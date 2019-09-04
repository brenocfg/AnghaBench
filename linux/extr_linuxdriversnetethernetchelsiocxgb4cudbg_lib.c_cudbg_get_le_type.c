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
typedef  scalar_t__ u32 ;
struct cudbg_tcam {scalar_t__ server_start; scalar_t__ filter_start; scalar_t__ clip_start; scalar_t__ routing_start; scalar_t__ tid_hash_base; scalar_t__ max_tid; } ;

/* Variables and functions */
 int LE_ET_HASH_CON ; 
 int LE_ET_INVALID_TID ; 
 int LE_ET_TCAM_CLIP ; 
 int LE_ET_TCAM_CON ; 
 int LE_ET_TCAM_FILTER ; 
 int LE_ET_TCAM_ROUTING ; 
 int LE_ET_TCAM_SERVER ; 
 int LE_ET_UNKNOWN ; 

__attribute__((used)) static int cudbg_get_le_type(u32 tid, struct cudbg_tcam tcam_region)
{
	int type = LE_ET_UNKNOWN;

	if (tid < tcam_region.server_start)
		type = LE_ET_TCAM_CON;
	else if (tid < tcam_region.filter_start)
		type = LE_ET_TCAM_SERVER;
	else if (tid < tcam_region.clip_start)
		type = LE_ET_TCAM_FILTER;
	else if (tid < tcam_region.routing_start)
		type = LE_ET_TCAM_CLIP;
	else if (tid < tcam_region.tid_hash_base)
		type = LE_ET_TCAM_ROUTING;
	else if (tid < tcam_region.max_tid)
		type = LE_ET_HASH_CON;
	else
		type = LE_ET_INVALID_TID;

	return type;
}