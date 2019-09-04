#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int myid; struct TYPE_4__* next; } ;
typedef  TYPE_1__ isdnloop_card ;

/* Variables and functions */
 TYPE_1__* cards ; 

__attribute__((used)) static inline isdnloop_card *
isdnloop_findcard(int driverid)
{
	isdnloop_card *p = cards;

	while (p) {
		if (p->myid == driverid)
			return p;
		p = p->next;
	}
	return (isdnloop_card *) 0;
}