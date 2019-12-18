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
struct bnxt_rx_ring_info {int /*<<< orphan*/  rx_prod; int /*<<< orphan*/  rx_db; int /*<<< orphan*/  rx_agg_prod; int /*<<< orphan*/  rx_agg_db; } ;
struct bnxt_napi {int events; struct bnxt_rx_ring_info* rx_ring; scalar_t__ tx_pkts; int /*<<< orphan*/  (* tx_int ) (struct bnxt*,struct bnxt_napi*,scalar_t__) ;} ;
struct bnxt {int dummy; } ;

/* Variables and functions */
 int BNXT_AGG_EVENT ; 
 int BNXT_RX_EVENT ; 
 int /*<<< orphan*/  bnxt_db_write (struct bnxt*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct bnxt*,struct bnxt_napi*,scalar_t__) ; 

__attribute__((used)) static void __bnxt_poll_work_done(struct bnxt *bp, struct bnxt_napi *bnapi)
{
	if (bnapi->tx_pkts) {
		bnapi->tx_int(bp, bnapi, bnapi->tx_pkts);
		bnapi->tx_pkts = 0;
	}

	if (bnapi->events & BNXT_RX_EVENT) {
		struct bnxt_rx_ring_info *rxr = bnapi->rx_ring;

		if (bnapi->events & BNXT_AGG_EVENT)
			bnxt_db_write(bp, &rxr->rx_agg_db, rxr->rx_agg_prod);
		bnxt_db_write(bp, &rxr->rx_db, rxr->rx_prod);
	}
	bnapi->events = 0;
}