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
struct TYPE_3__ {TYPE_2__* bas; } ;
struct cardstate {TYPE_1__ hw; } ;
struct TYPE_4__ {struct TYPE_4__* int_in_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 

__attribute__((used)) static void gigaset_freecshw(struct cardstate *cs)
{
	/* timers, URBs and rcvbuf are disposed of in disconnect */
	kfree(cs->hw.bas->int_in_buf);
	kfree(cs->hw.bas);
	cs->hw.bas = NULL;
}