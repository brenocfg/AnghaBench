#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct i2c_msg {int flags; scalar_t__ len; int* buf; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {scalar_t__ algo_data; } ;
struct hid_device {int dummy; } ;
struct cp2112_device {int hwversion; struct hid_device* hdev; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int CP2112_CANCEL_TRANSFER ; 
 int EBUSY ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HID_OUTPUT_REPORT ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  PM_HINT_FULLON ; 
 int /*<<< orphan*/  PM_HINT_NORMAL ; 
 unsigned int XFER_STATUS_RETRIES ; 
 int cp2112_hid_output (struct hid_device*,int*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ cp2112_i2c_write_read_req (int*,int /*<<< orphan*/ ,int*,scalar_t__,scalar_t__) ; 
 scalar_t__ cp2112_i2c_write_req (int*,int /*<<< orphan*/ ,int*,scalar_t__) ; 
 int cp2112_read (struct cp2112_device*,int*,scalar_t__) ; 
 scalar_t__ cp2112_read_req (int*,int /*<<< orphan*/ ,scalar_t__) ; 
 int cp2112_xfer_status (struct cp2112_device*) ; 
 int /*<<< orphan*/  hid_dbg (struct hid_device*,char*,int,...) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*,...) ; 
 int hid_hw_power (struct hid_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_warn (struct hid_device*,char*,...) ; 

__attribute__((used)) static int cp2112_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg *msgs,
			   int num)
{
	struct cp2112_device *dev = (struct cp2112_device *)adap->algo_data;
	struct hid_device *hdev = dev->hdev;
	u8 buf[64];
	ssize_t count;
	ssize_t read_length = 0;
	u8 *read_buf = NULL;
	unsigned int retries;
	int ret;

	hid_dbg(hdev, "I2C %d messages\n", num);

	if (num == 1) {
		if (msgs->flags & I2C_M_RD) {
			hid_dbg(hdev, "I2C read %#04x len %d\n",
				msgs->addr, msgs->len);
			read_length = msgs->len;
			read_buf = msgs->buf;
			count = cp2112_read_req(buf, msgs->addr, msgs->len);
		} else {
			hid_dbg(hdev, "I2C write %#04x len %d\n",
				msgs->addr, msgs->len);
			count = cp2112_i2c_write_req(buf, msgs->addr,
						     msgs->buf, msgs->len);
		}
		if (count < 0)
			return count;
	} else if (dev->hwversion > 1 &&  /* no repeated start in rev 1 */
		   num == 2 &&
		   msgs[0].addr == msgs[1].addr &&
		   !(msgs[0].flags & I2C_M_RD) && (msgs[1].flags & I2C_M_RD)) {
		hid_dbg(hdev, "I2C write-read %#04x wlen %d rlen %d\n",
			msgs[0].addr, msgs[0].len, msgs[1].len);
		read_length = msgs[1].len;
		read_buf = msgs[1].buf;
		count = cp2112_i2c_write_read_req(buf, msgs[0].addr,
				msgs[0].buf, msgs[0].len, msgs[1].len);
		if (count < 0)
			return count;
	} else {
		hid_err(hdev,
			"Multi-message I2C transactions not supported\n");
		return -EOPNOTSUPP;
	}

	ret = hid_hw_power(hdev, PM_HINT_FULLON);
	if (ret < 0) {
		hid_err(hdev, "power management error: %d\n", ret);
		return ret;
	}

	ret = cp2112_hid_output(hdev, buf, count, HID_OUTPUT_REPORT);
	if (ret < 0) {
		hid_warn(hdev, "Error starting transaction: %d\n", ret);
		goto power_normal;
	}

	for (retries = 0; retries < XFER_STATUS_RETRIES; ++retries) {
		ret = cp2112_xfer_status(dev);
		if (-EBUSY == ret)
			continue;
		if (ret < 0)
			goto power_normal;
		break;
	}

	if (XFER_STATUS_RETRIES <= retries) {
		hid_warn(hdev, "Transfer timed out, cancelling.\n");
		buf[0] = CP2112_CANCEL_TRANSFER;
		buf[1] = 0x01;

		ret = cp2112_hid_output(hdev, buf, 2, HID_OUTPUT_REPORT);
		if (ret < 0)
			hid_warn(hdev, "Error cancelling transaction: %d\n",
				 ret);

		ret = -ETIMEDOUT;
		goto power_normal;
	}

	for (count = 0; count < read_length;) {
		ret = cp2112_read(dev, read_buf + count, read_length - count);
		if (ret < 0)
			goto power_normal;
		if (ret == 0) {
			hid_err(hdev, "read returned 0\n");
			ret = -EIO;
			goto power_normal;
		}
		count += ret;
		if (count > read_length) {
			/*
			 * The hardware returned too much data.
			 * This is mostly harmless because cp2112_read()
			 * has a limit check so didn't overrun our
			 * buffer.  Nevertheless, we return an error
			 * because something is seriously wrong and
			 * it shouldn't go unnoticed.
			 */
			hid_err(hdev, "long read: %d > %zd\n",
				ret, read_length - count + ret);
			ret = -EIO;
			goto power_normal;
		}
	}

	/* return the number of transferred messages */
	ret = num;

power_normal:
	hid_hw_power(hdev, PM_HINT_NORMAL);
	hid_dbg(hdev, "I2C transfer finished: %d\n", ret);
	return ret;
}