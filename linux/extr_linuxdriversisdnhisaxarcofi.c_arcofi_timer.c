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
struct timer_list {int dummy; } ;
struct IsdnCardState {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  arcofitimer; } ;
struct TYPE_4__ {TYPE_1__ isac; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCOFI_TIMEOUT ; 
 int /*<<< orphan*/  arcofi_fsm (struct IsdnCardState*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct IsdnCardState* cs ; 
 TYPE_2__ dc ; 
 struct IsdnCardState* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
arcofi_timer(struct timer_list *t) {
	struct IsdnCardState *cs = from_timer(cs, t, dc.isac.arcofitimer);
	arcofi_fsm(cs, ARCOFI_TIMEOUT, NULL);
}