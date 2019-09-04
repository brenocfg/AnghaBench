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
struct TYPE_4__ {scalar_t__ nr_active; } ;
struct TYPE_3__ {scalar_t__ nr_waiting; } ;

/* Variables and functions */
 int MAX_NUMNODES ; 
 TYPE_2__* cbe_spu_info ; 
 TYPE_1__* spu_prio ; 

__attribute__((used)) static unsigned long count_active_contexts(void)
{
	int nr_active = 0, node;

	for (node = 0; node < MAX_NUMNODES; node++)
		nr_active += cbe_spu_info[node].nr_active;
	nr_active += spu_prio->nr_waiting;

	return nr_active;
}