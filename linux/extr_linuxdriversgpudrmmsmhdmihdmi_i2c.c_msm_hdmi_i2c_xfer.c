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
typedef  int uint32_t ;
struct i2c_msg {int addr; int flags; int len; int* buf; } ;
struct i2c_adapter {int dummy; } ;
struct hdmi_i2c_adapter {int /*<<< orphan*/  ddc_event; struct hdmi* hdmi; } ;
struct hdmi {struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,...) ; 
 int /*<<< orphan*/  DDC_READ ; 
 int /*<<< orphan*/  DDC_WRITE ; 
 int ETIMEDOUT ; 
 int FIELD (int,int (*) (int)) ; 
 int HDMI_CTRL_ENABLE ; 
 int HDMI_DDC_CTRL_GO ; 
 int HDMI_DDC_CTRL_TRANSACTION_CNT (int) ; 
 int HDMI_DDC_DATA_DATA (int) ; 
 int HDMI_DDC_DATA_DATA_RW (int /*<<< orphan*/ ) ; 
 int HDMI_DDC_DATA_INDEX (int) ; 
 int HDMI_DDC_DATA_INDEX_WRITE ; 
#define  HDMI_DDC_SW_STATUS_NACK0 131 
#define  HDMI_DDC_SW_STATUS_NACK1 130 
#define  HDMI_DDC_SW_STATUS_NACK2 129 
#define  HDMI_DDC_SW_STATUS_NACK3 128 
 int HDMI_I2C_TRANSACTION_REG_CNT (int) ; 
 int HDMI_I2C_TRANSACTION_REG_RW (int /*<<< orphan*/ ) ; 
 int HDMI_I2C_TRANSACTION_REG_START ; 
 int HDMI_I2C_TRANSACTION_REG_STOP ; 
 int HZ ; 
 int I2C_M_RD ; 
 int MAX_TRANSACTIONS ; 
 int /*<<< orphan*/  REG_HDMI_CTRL ; 
 int /*<<< orphan*/  REG_HDMI_DDC_CTRL ; 
 int /*<<< orphan*/  REG_HDMI_DDC_DATA ; 
 int /*<<< orphan*/  REG_HDMI_DDC_HW_STATUS ; 
 int /*<<< orphan*/  REG_HDMI_DDC_INT_CTRL ; 
 int /*<<< orphan*/  REG_HDMI_DDC_SW_STATUS ; 
 int /*<<< orphan*/  REG_HDMI_I2C_TRANSACTION (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int ddc_clear_irq (struct hdmi_i2c_adapter*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int hdmi_read (struct hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_write (struct hdmi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_ddc (struct hdmi_i2c_adapter*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  sw_done (struct hdmi_i2c_adapter*) ; 
 struct hdmi_i2c_adapter* to_hdmi_i2c_adapter (struct i2c_adapter*) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int msm_hdmi_i2c_xfer(struct i2c_adapter *i2c,
		struct i2c_msg *msgs, int num)
{
	struct hdmi_i2c_adapter *hdmi_i2c = to_hdmi_i2c_adapter(i2c);
	struct hdmi *hdmi = hdmi_i2c->hdmi;
	struct drm_device *dev = hdmi->dev;
	static const uint32_t nack[] = {
			HDMI_DDC_SW_STATUS_NACK0, HDMI_DDC_SW_STATUS_NACK1,
			HDMI_DDC_SW_STATUS_NACK2, HDMI_DDC_SW_STATUS_NACK3,
	};
	int indices[MAX_TRANSACTIONS];
	int ret, i, j, index = 0;
	uint32_t ddc_status, ddc_data, i2c_trans;

	num = min(num, MAX_TRANSACTIONS);

	WARN_ON(!(hdmi_read(hdmi, REG_HDMI_CTRL) & HDMI_CTRL_ENABLE));

	if (num == 0)
		return num;

	init_ddc(hdmi_i2c);

	ret = ddc_clear_irq(hdmi_i2c);
	if (ret)
		return ret;

	for (i = 0; i < num; i++) {
		struct i2c_msg *p = &msgs[i];
		uint32_t raw_addr = p->addr << 1;

		if (p->flags & I2C_M_RD)
			raw_addr |= 1;

		ddc_data = HDMI_DDC_DATA_DATA(raw_addr) |
				HDMI_DDC_DATA_DATA_RW(DDC_WRITE);

		if (i == 0) {
			ddc_data |= HDMI_DDC_DATA_INDEX(0) |
					HDMI_DDC_DATA_INDEX_WRITE;
		}

		hdmi_write(hdmi, REG_HDMI_DDC_DATA, ddc_data);
		index++;

		indices[i] = index;

		if (p->flags & I2C_M_RD) {
			index += p->len;
		} else {
			for (j = 0; j < p->len; j++) {
				ddc_data = HDMI_DDC_DATA_DATA(p->buf[j]) |
						HDMI_DDC_DATA_DATA_RW(DDC_WRITE);
				hdmi_write(hdmi, REG_HDMI_DDC_DATA, ddc_data);
				index++;
			}
		}

		i2c_trans = HDMI_I2C_TRANSACTION_REG_CNT(p->len) |
				HDMI_I2C_TRANSACTION_REG_RW(
						(p->flags & I2C_M_RD) ? DDC_READ : DDC_WRITE) |
				HDMI_I2C_TRANSACTION_REG_START;

		if (i == (num - 1))
			i2c_trans |= HDMI_I2C_TRANSACTION_REG_STOP;

		hdmi_write(hdmi, REG_HDMI_I2C_TRANSACTION(i), i2c_trans);
	}

	/* trigger the transfer: */
	hdmi_write(hdmi, REG_HDMI_DDC_CTRL,
			HDMI_DDC_CTRL_TRANSACTION_CNT(num - 1) |
			HDMI_DDC_CTRL_GO);

	ret = wait_event_timeout(hdmi_i2c->ddc_event, sw_done(hdmi_i2c), HZ/4);
	if (ret <= 0) {
		if (ret == 0)
			ret = -ETIMEDOUT;
		dev_warn(dev->dev, "DDC timeout: %d\n", ret);
		DBG("sw_status=%08x, hw_status=%08x, int_ctrl=%08x",
				hdmi_read(hdmi, REG_HDMI_DDC_SW_STATUS),
				hdmi_read(hdmi, REG_HDMI_DDC_HW_STATUS),
				hdmi_read(hdmi, REG_HDMI_DDC_INT_CTRL));
		return ret;
	}

	ddc_status = hdmi_read(hdmi, REG_HDMI_DDC_SW_STATUS);

	/* read back results of any read transactions: */
	for (i = 0; i < num; i++) {
		struct i2c_msg *p = &msgs[i];

		if (!(p->flags & I2C_M_RD))
			continue;

		/* check for NACK: */
		if (ddc_status & nack[i]) {
			DBG("ddc_status=%08x", ddc_status);
			break;
		}

		ddc_data = HDMI_DDC_DATA_DATA_RW(DDC_READ) |
				HDMI_DDC_DATA_INDEX(indices[i]) |
				HDMI_DDC_DATA_INDEX_WRITE;

		hdmi_write(hdmi, REG_HDMI_DDC_DATA, ddc_data);

		/* discard first byte: */
		hdmi_read(hdmi, REG_HDMI_DDC_DATA);

		for (j = 0; j < p->len; j++) {
			ddc_data = hdmi_read(hdmi, REG_HDMI_DDC_DATA);
			p->buf[j] = FIELD(ddc_data, HDMI_DDC_DATA_DATA);
		}
	}

	return i;
}