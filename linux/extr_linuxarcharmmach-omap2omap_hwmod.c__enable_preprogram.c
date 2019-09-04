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
struct omap_hwmod {TYPE_1__* class; } ;
struct TYPE_2__ {int (* enable_preprogram ) (struct omap_hwmod*) ;} ;

/* Variables and functions */
 int stub1 (struct omap_hwmod*) ; 

__attribute__((used)) static int _enable_preprogram(struct omap_hwmod *oh)
{
	if (!oh->class->enable_preprogram)
		return 0;

	return oh->class->enable_preprogram(oh);
}