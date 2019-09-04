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
typedef  int /*<<< orphan*/  u64 ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int /*<<< orphan*/  SN_MEMPROT_ACCESS_CLASS_0 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int sn_change_memprotect (unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xp ; 
 int xpSalError ; 
 int xpSuccess ; 

__attribute__((used)) static enum xp_retval
xp_restrict_memprotect_sn2(unsigned long phys_addr, unsigned long size)
{
	u64 nasid_array = 0;
	int ret;

	ret = sn_change_memprotect(phys_addr, size, SN_MEMPROT_ACCESS_CLASS_0,
				   &nasid_array);
	if (ret != 0) {
		dev_err(xp, "sn_change_memprotect(,, "
			"SN_MEMPROT_ACCESS_CLASS_0,) failed ret=%d\n", ret);
		return xpSalError;
	}
	return xpSuccess;
}