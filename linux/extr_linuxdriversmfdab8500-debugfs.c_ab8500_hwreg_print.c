#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct seq_file {struct device* private; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int shift; int mask; scalar_t__ addr; scalar_t__ bank; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ REG_FMT_DEC (TYPE_1__*) ; 
 int abx500_get_register_interruptible (struct device*,int,int,int*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int) ; 
 TYPE_1__ hwreg_cfg ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 

__attribute__((used)) static int ab8500_hwreg_print(struct seq_file *s, void *d)
{
	struct device *dev = s->private;
	int ret;
	u8 regvalue;

	ret = abx500_get_register_interruptible(dev,
		(u8)hwreg_cfg.bank, (u8)hwreg_cfg.addr, &regvalue);
	if (ret < 0) {
		dev_err(dev, "abx500_get_reg fail %d, %d\n",
			ret, __LINE__);
		return -EINVAL;
	}

	if (hwreg_cfg.shift >= 0)
		regvalue >>= hwreg_cfg.shift;
	else
		regvalue <<= -hwreg_cfg.shift;
	regvalue &= hwreg_cfg.mask;

	if (REG_FMT_DEC(&hwreg_cfg))
		seq_printf(s, "%d\n", regvalue);
	else
		seq_printf(s, "0x%02X\n", regvalue);
	return 0;
}