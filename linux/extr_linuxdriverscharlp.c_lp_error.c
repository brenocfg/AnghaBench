#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* dev; int /*<<< orphan*/  waitq; } ;
struct TYPE_7__ {TYPE_1__* port; } ;
struct TYPE_6__ {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int LP_ABORT ; 
 int LP_F (int) ; 
 int /*<<< orphan*/  LP_TIMEOUT_POLLED ; 
 scalar_t__ PARPORT_IRQ_NONE ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lp_claim_parport_or_block (TYPE_3__*) ; 
 int /*<<< orphan*/  lp_release_parport (TYPE_3__*) ; 
 TYPE_3__* lp_table ; 
 int /*<<< orphan*/  parport_yield_blocking (TYPE_2__*) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void lp_error (int minor)
{
	DEFINE_WAIT(wait);
	int polling;

	if (LP_F(minor) & LP_ABORT)
		return;

	polling = lp_table[minor].dev->port->irq == PARPORT_IRQ_NONE;
	if (polling) lp_release_parport (&lp_table[minor]);
	prepare_to_wait(&lp_table[minor].waitq, &wait, TASK_INTERRUPTIBLE);
	schedule_timeout(LP_TIMEOUT_POLLED);
	finish_wait(&lp_table[minor].waitq, &wait);
	if (polling) lp_claim_parport_or_block (&lp_table[minor]);
	else parport_yield_blocking (lp_table[minor].dev);
}