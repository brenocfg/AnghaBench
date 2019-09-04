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
struct cfq_group {scalar_t__ new_weight; scalar_t__ weight; } ;

/* Variables and functions */

__attribute__((used)) static void
cfq_update_group_weight(struct cfq_group *cfqg)
{
	if (cfqg->new_weight) {
		cfqg->weight = cfqg->new_weight;
		cfqg->new_weight = 0;
	}
}