#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vmbus_channel {int /*<<< orphan*/  callback_event; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HVUTIL_READY ; 
 TYPE_1__ kvp_transaction ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kvp_poll_wrapper(void *channel)
{
	/* Transaction is finished, reset the state here to avoid races. */
	kvp_transaction.state = HVUTIL_READY;
	tasklet_schedule(&((struct vmbus_channel *)channel)->callback_event);
}