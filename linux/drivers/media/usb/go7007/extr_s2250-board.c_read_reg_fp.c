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
typedef  int u16 ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
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
 int go7007_usb_vendor_request (struct go7007*,int,int,int /*<<< orphan*/ ,int*,int,int) ; 
 struct go7007* i2c_get_adapdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_reg_fp(struct i2c_client *client, u16 addr, u16 *val)
{
	struct go7007 *go = i2c_get_adapdata(client->adapter);
	struct go7007_usb *usb;
	int rc;
	u8 *buf;

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
	rc = go7007_usb_vendor_request(go, 0x58, addr, 0, buf, 16, 1);
	mutex_unlock(&usb->i2c_lock);
	if (rc < 0) {
		kfree(buf);
		return rc;
	}

	*val = (buf[0] << 8) | buf[1];
	kfree(buf);

	return 0;
}