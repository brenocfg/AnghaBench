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
 int /*<<< orphan*/  XP_MAX_NPARTITIONS_UV ; 
 int /*<<< orphan*/  is_uv () ; 
 int /*<<< orphan*/  sn_partition_id ; 
 int /*<<< orphan*/  sn_region_size ; 
 int xpSuccess ; 
 int /*<<< orphan*/  xp_cpu_to_nasid ; 
 int /*<<< orphan*/  xp_cpu_to_nasid_uv ; 
 int /*<<< orphan*/  xp_expand_memprotect ; 
 int /*<<< orphan*/  xp_expand_memprotect_uv ; 
 int /*<<< orphan*/  xp_max_npartitions ; 
 int /*<<< orphan*/  xp_pa ; 
 int /*<<< orphan*/  xp_pa_uv ; 
 int /*<<< orphan*/  xp_partition_id ; 
 int /*<<< orphan*/  xp_region_size ; 
 int /*<<< orphan*/  xp_remote_memcpy ; 
 int /*<<< orphan*/  xp_remote_memcpy_uv ; 
 int /*<<< orphan*/  xp_restrict_memprotect ; 
 int /*<<< orphan*/  xp_restrict_memprotect_uv ; 
 int /*<<< orphan*/  xp_socket_pa ; 
 int /*<<< orphan*/  xp_socket_pa_uv ; 

enum xp_retval
xp_init_uv(void)
{
	BUG_ON(!is_uv());

	xp_max_npartitions = XP_MAX_NPARTITIONS_UV;
#ifdef CONFIG_X86
	xp_partition_id = sn_partition_id;
	xp_region_size = sn_region_size;
#endif
	xp_pa = xp_pa_uv;
	xp_socket_pa = xp_socket_pa_uv;
	xp_remote_memcpy = xp_remote_memcpy_uv;
	xp_cpu_to_nasid = xp_cpu_to_nasid_uv;
	xp_expand_memprotect = xp_expand_memprotect_uv;
	xp_restrict_memprotect = xp_restrict_memprotect_uv;

	return xpSuccess;
}