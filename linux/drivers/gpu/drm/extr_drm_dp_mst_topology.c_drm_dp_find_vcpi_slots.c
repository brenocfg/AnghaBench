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
struct drm_dp_mst_topology_mgr {int /*<<< orphan*/  pbn_div; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int ENOSPC ; 

int drm_dp_find_vcpi_slots(struct drm_dp_mst_topology_mgr *mgr,
			   int pbn)
{
	int num_slots;

	num_slots = DIV_ROUND_UP(pbn, mgr->pbn_div);

	/* max. time slots - one slot for MTP header */
	if (num_slots > 63)
		return -ENOSPC;
	return num_slots;
}