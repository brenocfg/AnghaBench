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
struct TYPE_3__ {int /*<<< orphan*/  arcofi_wait; int /*<<< orphan*/  arcofitimer; } ;
struct TYPE_4__ {TYPE_1__ isac; } ;
struct IsdnCardState {int /*<<< orphan*/  HW_Flags; TYPE_2__ dc; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_ARCOFI ; 
 int /*<<< orphan*/  arcofi_timer ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
init_arcofi(struct IsdnCardState *cs) {
	timer_setup(&cs->dc.isac.arcofitimer, arcofi_timer, 0);
	init_waitqueue_head(&cs->dc.isac.arcofi_wait);
	test_and_set_bit(HW_ARCOFI, &cs->HW_Flags);
}