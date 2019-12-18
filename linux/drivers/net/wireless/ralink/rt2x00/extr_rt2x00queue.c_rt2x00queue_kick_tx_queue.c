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
struct txentry_desc {int /*<<< orphan*/  flags; } ;
struct data_queue {TYPE_3__* rt2x00dev; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {TYPE_1__* lib; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* kick_queue ) (struct data_queue*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_TXD_BURST ; 
 scalar_t__ rt2x00queue_threshold (struct data_queue*) ; 
 int /*<<< orphan*/  stub1 (struct data_queue*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt2x00queue_kick_tx_queue(struct data_queue *queue,
				      struct txentry_desc *txdesc)
{
	/*
	 * Check if we need to kick the queue, there are however a few rules
	 *	1) Don't kick unless this is the last in frame in a burst.
	 *	   When the burst flag is set, this frame is always followed
	 *	   by another frame which in some way are related to eachother.
	 *	   This is true for fragments, RTS or CTS-to-self frames.
	 *	2) Rule 1 can be broken when the available entries
	 *	   in the queue are less then a certain threshold.
	 */
	if (rt2x00queue_threshold(queue) ||
	    !test_bit(ENTRY_TXD_BURST, &txdesc->flags))
		queue->rt2x00dev->ops->lib->kick_queue(queue);
}