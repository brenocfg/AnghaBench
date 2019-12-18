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
struct mei_cl_cb {TYPE_1__* cl; } ;
struct TYPE_2__ {scalar_t__ tx_cb_queued; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mei_io_cb_free (struct mei_cl_cb*) ; 

__attribute__((used)) static inline void mei_tx_cb_dequeue(struct mei_cl_cb *cb)
{
	if (!WARN_ON(cb->cl->tx_cb_queued == 0))
		cb->cl->tx_cb_queued--;

	mei_io_cb_free(cb);
}