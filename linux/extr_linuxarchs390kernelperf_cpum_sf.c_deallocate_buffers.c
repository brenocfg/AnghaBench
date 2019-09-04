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
struct TYPE_2__ {scalar_t__ sdbt; } ;
struct cpu_hw_sf {TYPE_1__ sfb; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_sampling_buffer (TYPE_1__*) ; 

__attribute__((used)) static void deallocate_buffers(struct cpu_hw_sf *cpuhw)
{
	if (cpuhw->sfb.sdbt)
		free_sampling_buffer(&cpuhw->sfb);
}