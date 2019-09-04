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
typedef  scalar_t__ u8 ;
typedef  unsigned int u16 ;
struct s2250 {unsigned int reg12b_val; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
struct go7007_usb {int /*<<< orphan*/  i2c_lock; } ;
struct go7007 {scalar_t__ status; struct go7007_usb* hpi_context; } ;

/* Variables and functions */
 int EBUSY ; 
 int EFAULT ; 
 int EINTR ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ STATUS_SHUTDOWN ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int go7007_usb_vendor_request (struct go7007*,int,unsigned int,unsigned int,scalar_t__*,int,int) ; 
 struct go7007* i2c_get_adapdata (int /*<<< orphan*/ ) ; 
 struct s2250* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int write_reg_fp(struct i2c_client *client, u16 addr, u16 val)
{
	struct go7007 *go = i2c_get_adapdata(client->adapter);
	struct go7007_usb *usb;
	int rc;
	u8 *buf;
	struct s2250 *dec = i2c_get_clientdata(client);

	if (go == NULL)
		return -ENODEV;

	if (go->status == STATUS_SHUTDOWN)
		return -EBUSY;

	buf = kzalloc(16, GFP_KERNEL);

	if (buf == NULL)
		return -ENOMEM;



	memset(buf, 0xcd, 6);

	usb = go->hpi_context;
	if (mutex_lock_interruptible(&usb->i2c_lock) != 0) {
		dev_info(&client->dev, "i2c lock failed\n");
		kfree(buf);
		return -EINTR;
	}
	rc = go7007_usb_vendor_request(go, 0x57, addr, val, buf, 16, 1);
	mutex_unlock(&usb->i2c_lock);
	if (rc < 0) {
		kfree(buf);
		return rc;
	}

	if (buf[0] == 0) {
		unsigned int subaddr, val_read;

		subaddr = (buf[4] << 8) + buf[5];
		val_read = (buf[2] << 8) + buf[3];
		kfree(buf);
		if (val_read != val) {
			dev_info(&client->dev, "invalid fp write %x %x\n",
				 val_read, val);
			return -EFAULT;
		}
		if (subaddr != addr) {
			dev_info(&client->dev, "invalid fp write addr %x %x\n",
				 subaddr, addr);
			return -EFAULT;
		}
	} else {
		kfree(buf);
		return -EFAULT;
	}

	/* save last 12b value */
	if (addr == 0x12b)
		dec->reg12b_val = val;

	return 0;
}