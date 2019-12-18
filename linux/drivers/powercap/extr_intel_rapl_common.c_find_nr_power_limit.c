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
struct rapl_domain {TYPE_1__* rpl; } ;
struct TYPE_2__ {scalar_t__ name; } ;

/* Variables and functions */
 int NR_POWER_LIMITS ; 

__attribute__((used)) static int find_nr_power_limit(struct rapl_domain *rd)
{
	int i, nr_pl = 0;

	for (i = 0; i < NR_POWER_LIMITS; i++) {
		if (rd->rpl[i].name)
			nr_pl++;
	}

	return nr_pl;
}