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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 unsigned long intc_get_dfl_prio_level () ; 
 unsigned long simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uimask ; 

__attribute__((used)) static ssize_t
store_intc_userimask(struct device *dev,
		     struct device_attribute *attr,
		     const char *buf, size_t count)
{
	unsigned long level;

	level = simple_strtoul(buf, NULL, 10);

	/*
	 * Minimal acceptable IRQ levels are in the 2 - 16 range, but
	 * these are chomped so as to not interfere with normal IRQs.
	 *
	 * Level 1 is a special case on some CPUs in that it's not
	 * directly settable, but given that USERIMASK cuts off below a
	 * certain level, we don't care about this limitation here.
	 * Level 0 on the other hand equates to user masking disabled.
	 *
	 * We use the default priority level as a cut off so that only
	 * special case opt-in IRQs can be mangled.
	 */
	if (level >= intc_get_dfl_prio_level())
		return -EINVAL;

	__raw_writel(0xa5 << 24 | level << 4, uimask);

	return count;
}