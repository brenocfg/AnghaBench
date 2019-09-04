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
struct IsdnCardState {int /*<<< orphan*/  dbusytimer; int /*<<< orphan*/  tqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  Amd7930_bh ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbusy_timer_handler ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void setup_Amd7930(struct IsdnCardState *cs)
{
	INIT_WORK(&cs->tqueue, Amd7930_bh);
	timer_setup(&cs->dbusytimer, dbusy_timer_handler, 0);
}