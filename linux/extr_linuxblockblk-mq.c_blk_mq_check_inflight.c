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
struct request {TYPE_1__* part; } ;
struct mq_inflight {int /*<<< orphan*/ * inflight; TYPE_1__* part; } ;
struct blk_mq_hw_ctx {int dummy; } ;
struct TYPE_2__ {scalar_t__ partno; } ;

/* Variables and functions */

__attribute__((used)) static void blk_mq_check_inflight(struct blk_mq_hw_ctx *hctx,
				  struct request *rq, void *priv,
				  bool reserved)
{
	struct mq_inflight *mi = priv;

	/*
	 * index[0] counts the specific partition that was asked for. index[1]
	 * counts the ones that are active on the whole device, so increment
	 * that if mi->part is indeed a partition, and not a whole device.
	 */
	if (rq->part == mi->part)
		mi->inflight[0]++;
	if (mi->part->partno)
		mi->inflight[1]++;
}