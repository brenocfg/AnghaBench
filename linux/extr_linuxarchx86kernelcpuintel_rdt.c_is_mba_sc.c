#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int mba_sc; } ;
struct rdt_resource {TYPE_2__ membw; } ;
struct TYPE_4__ {int mba_sc; } ;
struct TYPE_6__ {TYPE_1__ membw; } ;

/* Variables and functions */
 size_t RDT_RESOURCE_MBA ; 
 TYPE_3__* rdt_resources_all ; 

bool is_mba_sc(struct rdt_resource *r)
{
	if (!r)
		return rdt_resources_all[RDT_RESOURCE_MBA].membw.mba_sc;

	return r->membw.mba_sc;
}