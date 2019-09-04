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
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long* __va (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned long,unsigned long const,size_t) ; 
 int gru_read_gpa (unsigned long*,unsigned long const) ; 
 int /*<<< orphan*/  uv_gpa_in_mmr_space (unsigned long const) ; 
 int /*<<< orphan*/  uv_gpa_to_soc_phys_ram (unsigned long) ; 
 int /*<<< orphan*/  xp ; 
 int xpGruCopyError ; 
 int xpSuccess ; 

__attribute__((used)) static enum xp_retval
xp_remote_mmr_read(unsigned long dst_gpa, const unsigned long src_gpa,
		   size_t len)
{
	int ret;
	unsigned long *dst_va = __va(uv_gpa_to_soc_phys_ram(dst_gpa));

	BUG_ON(!uv_gpa_in_mmr_space(src_gpa));
	BUG_ON(len != 8);

	ret = gru_read_gpa(dst_va, src_gpa);
	if (ret == 0)
		return xpSuccess;

	dev_err(xp, "gru_read_gpa() failed, dst_gpa=0x%016lx src_gpa=0x%016lx "
		"len=%ld\n", dst_gpa, src_gpa, len);
	return xpGruCopyError;
}