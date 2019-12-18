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
struct TYPE_4__ {int /*<<< orphan*/  skb_list; } ;
struct TYPE_3__ {scalar_t__ txavail; } ;
struct dma_info {TYPE_2__ ampdu_session; int /*<<< orphan*/  txout; int /*<<< orphan*/  txin; scalar_t__ ntxd; TYPE_1__ dma; } ;

/* Variables and functions */
 scalar_t__ ntxdactive (struct dma_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dma_update_txavail(struct dma_info *di)
{
	/*
	 * Available space is number of descriptors less the number of
	 * active descriptors and the number of queued AMPDU frames.
	 */
	di->dma.txavail = di->ntxd - ntxdactive(di, di->txin, di->txout) -
			  skb_queue_len(&di->ampdu_session.skb_list) - 1;
}