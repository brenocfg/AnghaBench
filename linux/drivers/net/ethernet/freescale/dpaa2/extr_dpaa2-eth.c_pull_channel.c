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
struct TYPE_2__ {int dequeue_portal_busy; int /*<<< orphan*/  pull_err; } ;
struct dpaa2_eth_channel {TYPE_1__ stats; int /*<<< orphan*/  store; int /*<<< orphan*/  ch_id; int /*<<< orphan*/  dpio; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int dpaa2_io_service_pull_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int pull_channel(struct dpaa2_eth_channel *ch)
{
	int err;
	int dequeues = -1;

	/* Retry while portal is busy */
	do {
		err = dpaa2_io_service_pull_channel(ch->dpio, ch->ch_id,
						    ch->store);
		dequeues++;
		cpu_relax();
	} while (err == -EBUSY);

	ch->stats.dequeue_portal_busy += dequeues;
	if (unlikely(err))
		ch->stats.pull_err++;

	return err;
}