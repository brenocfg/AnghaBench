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
typedef  enum irq_remap_cap { ____Placeholder_irq_remap_cap } irq_remap_cap ;
struct TYPE_2__ {int capability; } ;

/* Variables and functions */
 scalar_t__ disable_irq_post ; 
 TYPE_1__* remap_ops ; 

bool irq_remapping_cap(enum irq_remap_cap cap)
{
	if (!remap_ops || disable_irq_post)
		return false;

	return (remap_ops->capability & (1 << cap));
}