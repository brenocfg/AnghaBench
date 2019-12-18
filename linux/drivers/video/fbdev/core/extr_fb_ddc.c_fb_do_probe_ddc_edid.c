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
struct i2c_msg {int len; unsigned char* buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDC_ADDR ; 
 int EDID_LENGTH ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char *fb_do_probe_ddc_edid(struct i2c_adapter *adapter)
{
	unsigned char start = 0x0;
	unsigned char *buf = kmalloc(EDID_LENGTH, GFP_KERNEL);
	struct i2c_msg msgs[] = {
		{
			.addr	= DDC_ADDR,
			.flags	= 0,
			.len	= 1,
			.buf	= &start,
		}, {
			.addr	= DDC_ADDR,
			.flags	= I2C_M_RD,
			.len	= EDID_LENGTH,
			.buf	= buf,
		}
	};

	if (!buf) {
		dev_warn(&adapter->dev, "unable to allocate memory for EDID "
			 "block.\n");
		return NULL;
	}

	if (i2c_transfer(adapter, msgs, 2) == 2)
		return buf;

	dev_warn(&adapter->dev, "unable to read EDID block.\n");
	kfree(buf);
	return NULL;
}