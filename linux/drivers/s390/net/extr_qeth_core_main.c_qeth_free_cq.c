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
struct TYPE_2__ {int /*<<< orphan*/ * out_bufstates; int /*<<< orphan*/ * c_q; int /*<<< orphan*/  no_in_queues; } ;
struct qeth_card {TYPE_1__ qdio; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_free_qdio_queue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qeth_free_cq(struct qeth_card *card)
{
	if (card->qdio.c_q) {
		--card->qdio.no_in_queues;
		qeth_free_qdio_queue(card->qdio.c_q);
		card->qdio.c_q = NULL;
	}
	kfree(card->qdio.out_bufstates);
	card->qdio.out_bufstates = NULL;
}