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
struct ide_timing {void* udma; void* cycle; void* recover; void* active; void* cyc8b; void* rec8b; void* act8b; void* setup; } ;

/* Variables and functions */
 void* EZ (void*,int) ; 

__attribute__((used)) static void ide_timing_quantize(struct ide_timing *t, struct ide_timing *q,
				int T, int UT)
{
	q->setup   = EZ(t->setup,   T);
	q->act8b   = EZ(t->act8b,   T);
	q->rec8b   = EZ(t->rec8b,   T);
	q->cyc8b   = EZ(t->cyc8b,   T);
	q->active  = EZ(t->active,  T);
	q->recover = EZ(t->recover, T);
	q->cycle   = EZ(t->cycle,   T);
	q->udma    = EZ(t->udma,    UT);
}