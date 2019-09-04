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
struct kyber_hctx_data {int /*<<< orphan*/ * kcq_map; int /*<<< orphan*/ * rqs; } ;
struct blk_mq_hw_ctx {struct kyber_hctx_data* sched_data; } ;

/* Variables and functions */
 int KYBER_NUM_DOMAINS ; 
 int /*<<< orphan*/  list_empty_careful (int /*<<< orphan*/ *) ; 
 scalar_t__ sbitmap_any_bit_set (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool kyber_has_work(struct blk_mq_hw_ctx *hctx)
{
	struct kyber_hctx_data *khd = hctx->sched_data;
	int i;

	for (i = 0; i < KYBER_NUM_DOMAINS; i++) {
		if (!list_empty_careful(&khd->rqs[i]) ||
		    sbitmap_any_bit_set(&khd->kcq_map[i]))
			return true;
	}

	return false;
}