#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct IsdnCardState {TYPE_2__* bcs; } ;
struct TYPE_6__ {int /*<<< orphan*/ * send; } ;
struct TYPE_4__ {TYPE_3__ hfc; } ;
struct TYPE_5__ {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void
releasehfc(struct IsdnCardState *cs)
{
	kfree(cs->bcs[0].hw.hfc.send);
	cs->bcs[0].hw.hfc.send = NULL;
	kfree(cs->bcs[1].hw.hfc.send);
	cs->bcs[1].hw.hfc.send = NULL;
}