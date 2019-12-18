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
typedef  scalar_t__ u32 ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_GET_FUNC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpup (int /*<<< orphan*/ *) ; 
 int usb_read (struct i2c_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static u32 usb_func(struct i2c_adapter *adapter)
{
	__le32 *pfunc;
	u32 ret;

	pfunc = kmalloc(sizeof(*pfunc), GFP_KERNEL);

	/* get functionality from adapter */
	if (!pfunc || usb_read(adapter, CMD_GET_FUNC, 0, 0, pfunc,
			       sizeof(*pfunc)) != sizeof(*pfunc)) {
		dev_err(&adapter->dev, "failure reading functionality\n");
		ret = 0;
		goto out;
	}

	ret = le32_to_cpup(pfunc);
out:
	kfree(pfunc);
	return ret;
}