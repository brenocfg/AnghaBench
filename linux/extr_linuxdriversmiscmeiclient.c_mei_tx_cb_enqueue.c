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
struct mei_cl_cb {TYPE_1__* cl; int /*<<< orphan*/  list; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_cb_queued; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static inline void mei_tx_cb_enqueue(struct mei_cl_cb *cb,
				     struct list_head *head)
{
	list_add_tail(&cb->list, head);
	cb->cl->tx_cb_queued++;
}