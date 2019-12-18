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
struct dm_region {TYPE_1__* rh; } ;
struct TYPE_2__ {void* context; } ;

/* Variables and functions */

void *dm_rh_region_context(struct dm_region *reg)
{
	return reg->rh->context;
}