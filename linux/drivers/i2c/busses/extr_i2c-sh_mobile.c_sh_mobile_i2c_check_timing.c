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
typedef  scalar_t__ u16 ;
struct sh_mobile_i2c_data {int flags; scalar_t__ iccl; scalar_t__ icch; int /*<<< orphan*/  dev; int /*<<< orphan*/  icic; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ICIC_ICCHB8 ; 
 int /*<<< orphan*/  ICIC_ICCLB8 ; 
 int IIC_FLAG_HAS_ICIC67 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int sh_mobile_i2c_check_timing(struct sh_mobile_i2c_data *pd)
{
	u16 max_val = pd->flags & IIC_FLAG_HAS_ICIC67 ? 0x1ff : 0xff;

	if (pd->iccl > max_val || pd->icch > max_val) {
		dev_err(pd->dev, "timing values out of range: L/H=0x%x/0x%x\n",
			pd->iccl, pd->icch);
		return -EINVAL;
	}

	/* one more bit of ICCL in ICIC */
	if (pd->iccl & 0x100)
		pd->icic |= ICIC_ICCLB8;
	else
		pd->icic &= ~ICIC_ICCLB8;

	/* one more bit of ICCH in ICIC */
	if (pd->icch & 0x100)
		pd->icic |= ICIC_ICCHB8;
	else
		pd->icic &= ~ICIC_ICCHB8;

	dev_dbg(pd->dev, "timing values: L/H=0x%x/0x%x\n", pd->iccl, pd->icch);
	return 0;
}