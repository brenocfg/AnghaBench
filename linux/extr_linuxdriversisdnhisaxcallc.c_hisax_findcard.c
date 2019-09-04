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
struct IsdnCardState {int myid; } ;
struct TYPE_2__ {struct IsdnCardState* cs; } ;

/* Variables and functions */
 TYPE_1__* cards ; 
 int nrcards ; 

__attribute__((used)) static inline struct IsdnCardState *
hisax_findcard(int driverid)
{
	int i;

	for (i = 0; i < nrcards; i++)
		if (cards[i].cs)
			if (cards[i].cs->myid == driverid)
				return (cards[i].cs);
	return (struct IsdnCardState *) 0;
}