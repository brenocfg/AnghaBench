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
struct tid_info {unsigned int nsftids; unsigned int sftid_base; unsigned int nstids; TYPE_1__* stid_tab; scalar_t__ stid_base; } ;
struct TYPE_2__ {void* data; } ;

/* Variables and functions */

__attribute__((used)) static inline void *lookup_stid(const struct tid_info *t, unsigned int stid)
{
	/* Is it a server filter TID? */
	if (t->nsftids && (stid >= t->sftid_base)) {
		stid -= t->sftid_base;
		stid += t->nstids;
	} else {
		stid -= t->stid_base;
	}

	return stid < (t->nstids + t->nsftids) ? t->stid_tab[stid].data : NULL;
}