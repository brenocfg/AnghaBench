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
struct sdma_state {int dummy; } ;
struct sdma_engine {TYPE_1__* dd; struct sdma_state state; } ;
struct TYPE_2__ {int /*<<< orphan*/  sdma_unfreeze_wq; int /*<<< orphan*/  sdma_unfreeze_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sdma_put (struct sdma_state*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sdma_sw_tear_down(struct sdma_engine *sde)
{
	struct sdma_state *ss = &sde->state;

	/* Releasing this reference means the state machine has stopped. */
	sdma_put(ss);

	/* stop waiting for all unfreeze events to complete */
	atomic_set(&sde->dd->sdma_unfreeze_count, -1);
	wake_up_interruptible(&sde->dd->sdma_unfreeze_wq);
}