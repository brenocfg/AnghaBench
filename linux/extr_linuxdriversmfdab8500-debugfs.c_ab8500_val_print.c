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
typedef  int /*<<< orphan*/  u8 ;
struct seq_file {struct device* private; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int abx500_get_register_interruptible (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ debug_address ; 
 scalar_t__ debug_bank ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ab8500_val_print(struct seq_file *s, void *p)
{
	struct device *dev = s->private;
	int ret;
	u8 regvalue;

	ret = abx500_get_register_interruptible(dev,
		(u8)debug_bank, (u8)debug_address, &regvalue);
	if (ret < 0) {
		dev_err(dev, "abx500_get_reg fail %d, %d\n",
			ret, __LINE__);
		return -EINVAL;
	}
	seq_printf(s, "0x%02X\n", regvalue);

	return 0;
}