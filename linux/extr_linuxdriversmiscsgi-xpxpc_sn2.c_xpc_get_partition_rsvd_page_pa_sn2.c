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
typedef  scalar_t__ s64 ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 scalar_t__ SALRET_MORE_PASSES ; 
 scalar_t__ SALRET_OK ; 
 scalar_t__ sn_partition_reserved_page_pa (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int xpNeedMoreInfo ; 
 int xpSalError ; 
 int xpSuccess ; 

__attribute__((used)) static enum xp_retval
xpc_get_partition_rsvd_page_pa_sn2(void *buf, u64 *cookie, unsigned long *rp_pa,
				   size_t *len)
{
	s64 status;
	enum xp_retval ret;

	status = sn_partition_reserved_page_pa((u64)buf, cookie,
			(u64 *)rp_pa, (u64 *)len);
	if (status == SALRET_OK)
		ret = xpSuccess;
	else if (status == SALRET_MORE_PASSES)
		ret = xpNeedMoreInfo;
	else
		ret = xpSalError;

	return ret;
}