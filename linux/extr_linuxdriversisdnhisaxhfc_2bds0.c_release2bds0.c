#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * send; } ;
struct TYPE_7__ {TYPE_1__ hfcD; } ;
struct IsdnCardState {TYPE_2__ hw; TYPE_5__* bcs; } ;
struct TYPE_8__ {int /*<<< orphan*/ * send; } ;
struct TYPE_9__ {TYPE_3__ hfc; } ;
struct TYPE_10__ {TYPE_4__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void
release2bds0(struct IsdnCardState *cs)
{
	kfree(cs->bcs[0].hw.hfc.send);
	cs->bcs[0].hw.hfc.send = NULL;
	kfree(cs->bcs[1].hw.hfc.send);
	cs->bcs[1].hw.hfc.send = NULL;
	kfree(cs->hw.hfcD.send);
	cs->hw.hfcD.send = NULL;
}