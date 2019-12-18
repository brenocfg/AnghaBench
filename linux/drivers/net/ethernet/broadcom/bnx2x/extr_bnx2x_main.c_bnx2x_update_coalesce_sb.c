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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HC_INDEX_ETH_RX_CQ_CONS ; 
 int /*<<< orphan*/  HC_INDEX_ETH_TX_CQ_CONS_COS0 ; 
 int /*<<< orphan*/  HC_INDEX_ETH_TX_CQ_CONS_COS1 ; 
 int /*<<< orphan*/  HC_INDEX_ETH_TX_CQ_CONS_COS2 ; 
 int /*<<< orphan*/  bnx2x_update_coalesce_sb_index (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_update_coalesce_sb(struct bnx2x *bp, u8 fw_sb_id,
				     u16 tx_usec, u16 rx_usec)
{
	bnx2x_update_coalesce_sb_index(bp, fw_sb_id, HC_INDEX_ETH_RX_CQ_CONS,
				    false, rx_usec);
	bnx2x_update_coalesce_sb_index(bp, fw_sb_id,
				       HC_INDEX_ETH_TX_CQ_CONS_COS0, false,
				       tx_usec);
	bnx2x_update_coalesce_sb_index(bp, fw_sb_id,
				       HC_INDEX_ETH_TX_CQ_CONS_COS1, false,
				       tx_usec);
	bnx2x_update_coalesce_sb_index(bp, fw_sb_id,
				       HC_INDEX_ETH_TX_CQ_CONS_COS2, false,
				       tx_usec);
}