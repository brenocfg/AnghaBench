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
struct qeth_qdio_out_q {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_TX_TIMER_USECS ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 
 scalar_t__ usecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void qeth_tx_arm_timer(struct qeth_qdio_out_q *queue)
{
	if (timer_pending(&queue->timer))
		return;
	mod_timer(&queue->timer, usecs_to_jiffies(QETH_TX_TIMER_USECS) +
				 jiffies);
}