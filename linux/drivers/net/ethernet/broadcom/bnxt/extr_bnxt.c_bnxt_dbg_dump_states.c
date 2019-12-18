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
struct bnxt_napi {int dummy; } ;
struct bnxt {int cp_nr_rings; struct bnxt_napi** bnapi; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_dump_cp_sw_state (struct bnxt_napi*) ; 
 int /*<<< orphan*/  bnxt_dump_rx_sw_state (struct bnxt_napi*) ; 
 int /*<<< orphan*/  bnxt_dump_tx_sw_state (struct bnxt_napi*) ; 
 scalar_t__ netif_msg_drv (struct bnxt*) ; 

__attribute__((used)) static void bnxt_dbg_dump_states(struct bnxt *bp)
{
	int i;
	struct bnxt_napi *bnapi;

	for (i = 0; i < bp->cp_nr_rings; i++) {
		bnapi = bp->bnapi[i];
		if (netif_msg_drv(bp)) {
			bnxt_dump_tx_sw_state(bnapi);
			bnxt_dump_rx_sw_state(bnapi);
			bnxt_dump_cp_sw_state(bnapi);
		}
	}
}