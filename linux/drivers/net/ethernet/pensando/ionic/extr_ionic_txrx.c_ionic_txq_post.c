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
struct ionic_queue {TYPE_1__* head; } ;
typedef  int /*<<< orphan*/  ionic_desc_cb ;
struct TYPE_2__ {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_STATS_TXQ_POST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ionic_q_post (struct ionic_queue*,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  q_to_qcq (struct ionic_queue*) ; 

__attribute__((used)) static inline void ionic_txq_post(struct ionic_queue *q, bool ring_dbell,
				  ionic_desc_cb cb_func, void *cb_arg)
{
	DEBUG_STATS_TXQ_POST(q_to_qcq(q), q->head->desc, ring_dbell);

	ionic_q_post(q, ring_dbell, cb_func, cb_arg);
}