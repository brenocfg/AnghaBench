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
union partition_info_u {int hub_version; long partition_id; long coherence_id; long region_size; void* val; } ;
typedef  void* u64 ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 scalar_t__ BIOS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  UV_BIOS_GET_SN_INFO ; 
 scalar_t__ uv_bios_call_irqsave (int /*<<< orphan*/ ,int,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s64 uv_bios_get_sn_info(int fc, int *uvtype, long *partid, long *coher,
		long *region, long *ssn)
{
	s64 ret;
	u64 v0, v1;
	union partition_info_u part;

	ret = uv_bios_call_irqsave(UV_BIOS_GET_SN_INFO, fc,
				(u64)(&v0), (u64)(&v1), 0, 0);
	if (ret != BIOS_STATUS_SUCCESS)
		return ret;

	part.val = v0;
	if (uvtype)
		*uvtype = part.hub_version;
	if (partid)
		*partid = part.partition_id;
	if (coher)
		*coher = part.coherence_id;
	if (region)
		*region = part.region_size;
	if (ssn)
		*ssn = v1;
	return ret;
}