#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ num_busy_placement; scalar_t__ num_placement; TYPE_2__* busy_placement; TYPE_2__* placement; } ;
struct qxl_bo {TYPE_2__* placements; TYPE_1__ placement; } ;
struct TYPE_4__ {scalar_t__ lpfn; scalar_t__ fpfn; scalar_t__ flags; } ;

/* Variables and functions */
 scalar_t__ QXL_GEM_DOMAIN_CPU ; 
 scalar_t__ QXL_GEM_DOMAIN_SURFACE ; 
 scalar_t__ QXL_GEM_DOMAIN_VRAM ; 
 scalar_t__ TTM_PL_FLAG_CACHED ; 
 scalar_t__ TTM_PL_FLAG_NO_EVICT ; 
 scalar_t__ TTM_PL_FLAG_PRIV ; 
 scalar_t__ TTM_PL_FLAG_SYSTEM ; 
 scalar_t__ TTM_PL_FLAG_VRAM ; 
 scalar_t__ TTM_PL_MASK_CACHING ; 

void qxl_ttm_placement_from_domain(struct qxl_bo *qbo, u32 domain, bool pinned)
{
	u32 c = 0;
	u32 pflag = pinned ? TTM_PL_FLAG_NO_EVICT : 0;
	unsigned i;

	qbo->placement.placement = qbo->placements;
	qbo->placement.busy_placement = qbo->placements;
	if (domain == QXL_GEM_DOMAIN_VRAM)
		qbo->placements[c++].flags = TTM_PL_FLAG_CACHED | TTM_PL_FLAG_VRAM | pflag;
	if (domain == QXL_GEM_DOMAIN_SURFACE)
		qbo->placements[c++].flags = TTM_PL_FLAG_CACHED | TTM_PL_FLAG_PRIV | pflag;
	if (domain == QXL_GEM_DOMAIN_CPU)
		qbo->placements[c++].flags = TTM_PL_MASK_CACHING | TTM_PL_FLAG_SYSTEM | pflag;
	if (!c)
		qbo->placements[c++].flags = TTM_PL_MASK_CACHING | TTM_PL_FLAG_SYSTEM;
	qbo->placement.num_placement = c;
	qbo->placement.num_busy_placement = c;
	for (i = 0; i < c; ++i) {
		qbo->placements[i].fpfn = 0;
		qbo->placements[i].lpfn = 0;
	}
}