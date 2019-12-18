#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union ionic_adminq_cmd {int dummy; } ionic_adminq_cmd ;
struct ionic_queue {TYPE_1__* tail; TYPE_1__* head; } ;
struct ionic_lif {int /*<<< orphan*/  adminq_lock; TYPE_2__* adminqcq; } ;
struct TYPE_4__ {struct ionic_queue q; } ;
struct TYPE_3__ {struct TYPE_3__* next; int /*<<< orphan*/ * cb_arg; int /*<<< orphan*/ * cb; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ionic_adminq_flush(struct ionic_lif *lif)
{
	struct ionic_queue *adminq = &lif->adminqcq->q;

	spin_lock(&lif->adminq_lock);

	while (adminq->tail != adminq->head) {
		memset(adminq->tail->desc, 0, sizeof(union ionic_adminq_cmd));
		adminq->tail->cb = NULL;
		adminq->tail->cb_arg = NULL;
		adminq->tail = adminq->tail->next;
	}
	spin_unlock(&lif->adminq_lock);
}