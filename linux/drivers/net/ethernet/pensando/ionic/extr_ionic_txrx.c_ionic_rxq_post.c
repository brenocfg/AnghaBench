#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ionic_queue {int dummy; } ;
typedef  int /*<<< orphan*/  ionic_desc_cb ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_STATS_RX_BUFF_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ionic_q_post (struct ionic_queue*,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  q_to_qcq (struct ionic_queue*) ; 

__attribute__((used)) static inline void ionic_rxq_post(struct ionic_queue *q, bool ring_dbell,
				  ionic_desc_cb cb_func, void *cb_arg)
{
	ionic_q_post(q, ring_dbell, cb_func, cb_arg);

	DEBUG_STATS_RX_BUFF_CNT(q_to_qcq(q));
}