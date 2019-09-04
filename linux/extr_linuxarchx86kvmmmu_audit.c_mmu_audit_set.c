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
struct kernel_param {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mmu_audit_disable () ; 
 int /*<<< orphan*/  mmu_audit_enable () ; 

__attribute__((used)) static int mmu_audit_set(const char *val, const struct kernel_param *kp)
{
	int ret;
	unsigned long enable;

	ret = kstrtoul(val, 10, &enable);
	if (ret < 0)
		return -EINVAL;

	switch (enable) {
	case 0:
		mmu_audit_disable();
		break;
	case 1:
		mmu_audit_enable();
		break;
	default:
		return -EINVAL;
	}

	return 0;
}