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
typedef  int /*<<< orphan*/  u32 ;
struct dsaf_device {int /*<<< orphan*/  sc_base; int /*<<< orphan*/  dev; scalar_t__ sub_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dsaf_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dsaf_read_syscon (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 dsaf_read_sub(struct dsaf_device *dsaf_dev, u32 reg)
{
	u32 ret = 0;
	int err;

	if (dsaf_dev->sub_ctrl) {
		err = dsaf_read_syscon(dsaf_dev->sub_ctrl, reg, &ret);
		if (err)
			dev_err(dsaf_dev->dev, "dsaf_read_syscon error %d!\n",
				err);
	} else {
		ret = dsaf_read_reg(dsaf_dev->sc_base, reg);
	}

	return ret;
}