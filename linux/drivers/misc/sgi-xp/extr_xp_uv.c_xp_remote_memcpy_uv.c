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
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned long,unsigned long const,size_t) ; 
 int gru_copy_gpa (unsigned long,unsigned long const,size_t) ; 
 scalar_t__ uv_gpa_in_mmr_space (unsigned long const) ; 
 int /*<<< orphan*/  xp ; 
 int xpGruCopyError ; 
 int xpSuccess ; 
 int xp_remote_mmr_read (unsigned long,unsigned long const,size_t) ; 

__attribute__((used)) static enum xp_retval
xp_remote_memcpy_uv(unsigned long dst_gpa, const unsigned long src_gpa,
		    size_t len)
{
	int ret;

	if (uv_gpa_in_mmr_space(src_gpa))
		return xp_remote_mmr_read(dst_gpa, src_gpa, len);

	ret = gru_copy_gpa(dst_gpa, src_gpa, len);
	if (ret == 0)
		return xpSuccess;

	dev_err(xp, "gru_copy_gpa() failed, dst_gpa=0x%016lx src_gpa=0x%016lx "
		"len=%ld\n", dst_gpa, src_gpa, len);
	return xpGruCopyError;
}