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
typedef  int /*<<< orphan*/  u32 ;
struct rsi_hw {int /*<<< orphan*/  (* determine_event_timeout ) (struct rsi_hw*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  completion; int /*<<< orphan*/  event; int /*<<< orphan*/  thread_done; } ;
struct rsi_common {TYPE_1__ tx_thread; scalar_t__ init_done; struct rsi_hw* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_WAIT_FOREVER ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete_and_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsi_core_qos_processor (struct rsi_common*) ; 
 int /*<<< orphan*/  rsi_reset_event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsi_wait_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct rsi_hw*) ; 

__attribute__((used)) static void rsi_tx_scheduler_thread(struct rsi_common *common)
{
	struct rsi_hw *adapter = common->priv;
	u32 timeout = EVENT_WAIT_FOREVER;

	do {
		if (adapter->determine_event_timeout)
			timeout = adapter->determine_event_timeout(adapter);
		rsi_wait_event(&common->tx_thread.event, timeout);
		rsi_reset_event(&common->tx_thread.event);

		if (common->init_done)
			rsi_core_qos_processor(common);
	} while (atomic_read(&common->tx_thread.thread_done) == 0);
	complete_and_exit(&common->tx_thread.completion, 0);
}