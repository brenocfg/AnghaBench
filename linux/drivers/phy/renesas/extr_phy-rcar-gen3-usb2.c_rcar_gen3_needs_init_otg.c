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
struct rcar_gen3_chan {TYPE_1__* rphys; } ;
struct TYPE_2__ {scalar_t__ otg_initialized; } ;

/* Variables and functions */
 int NUM_OF_PHYS ; 

__attribute__((used)) static bool rcar_gen3_needs_init_otg(struct rcar_gen3_chan *ch)
{
	int i;

	for (i = 0; i < NUM_OF_PHYS; i++) {
		if (ch->rphys[i].otg_initialized)
			return false;
	}

	return true;
}