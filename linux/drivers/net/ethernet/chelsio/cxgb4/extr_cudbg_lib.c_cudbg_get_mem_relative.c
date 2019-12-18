#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct cudbg_meminfo {TYPE_1__* avail; } ;
struct adapter {int dummy; } ;
struct TYPE_2__ {scalar_t__ base; scalar_t__ limit; } ;

/* Variables and functions */
 int cudbg_meminfo_get_mem_index (struct adapter*,struct cudbg_meminfo*,size_t,size_t*) ; 

__attribute__((used)) static int cudbg_get_mem_relative(struct adapter *padap,
				  struct cudbg_meminfo *meminfo,
				  u8 mem_type, u32 *out_base, u32 *out_end)
{
	u8 mc_idx;
	int rc;

	rc = cudbg_meminfo_get_mem_index(padap, meminfo, mem_type, &mc_idx);
	if (rc)
		return rc;

	if (*out_base < meminfo->avail[mc_idx].base)
		*out_base = 0;
	else
		*out_base -= meminfo->avail[mc_idx].base;

	if (*out_end > meminfo->avail[mc_idx].limit)
		*out_end = meminfo->avail[mc_idx].limit;
	else
		*out_end -= meminfo->avail[mc_idx].base;

	return 0;
}