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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {TYPE_1__* plat_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  cpu_cache_flags; } ;

/* Variables and functions */
 TYPE_2__* omap_dmm ; 

u32 tiler_get_cpu_cache_flags(void)
{
	return omap_dmm->plat_data->cpu_cache_flags;
}