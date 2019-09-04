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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {int n_blacklist_ev; scalar_t__* blacklist_ev; } ;

/* Variables and functions */
 TYPE_1__* ppmu ; 

__attribute__((used)) static bool is_event_blacklisted(u64 ev)
{
	int i;

	for (i=0; i < ppmu->n_blacklist_ev; i++) {
		if (ppmu->blacklist_ev[i] == ev)
			return true;
	}

	return false;
}