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
struct i2c_client {int addr; int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
struct go7007_usb {int /*<<< orphan*/  i2c_lock; } ;
struct go7007 {scalar_t__ status; struct go7007_usb* hpi_context; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINTR ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ STATUS_SHUTDOWN ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int go7007_usb_vendor_request (struct go7007*,int,int,int,int*,int,int) ; 
 struct go7007* i2c_get_adapdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int write_reg(struct i2c_client *client, u8 reg, u8 value)
{
	struct go7007 *go = i2c_get_adapdata(client->adapter);
	struct go7007_usb *usb;
	int rc;
	int dev_addr = client->addr << 1;  /* firmware wants 8-bit address */
	u8 *buf;

	if (go == NULL)
		return -ENODEV;

	if (go->status == STATUS_SHUTDOWN)
		return -EBUSY;

	buf = kzalloc(16, GFP_KERNEL);
	if (buf == NULL)
		return -ENOMEM;

	usb = go->hpi_context;
	if (mutex_lock_interruptible(&usb->i2c_lock) != 0) {
		dev_info(&client->dev, "i2c lock failed\n");
		kfree(buf);
		return -EINTR;
	}
	rc = go7007_usb_vendor_request(go, 0x55, dev_addr,
				       (reg<<8 | value),
				       buf,
				       16, 1);

	mutex_unlock(&usb->i2c_lock);
	kfree(buf);
	return rc;
}