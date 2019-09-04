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
typedef  int u64 ;
typedef  int u32 ;
struct bnx2_tx_ring_info {scalar_t__ tx_desc_mapping; } ;
struct bnx2 {int dummy; } ;

/* Variables and functions */
 scalar_t__ BNX2_CHIP (struct bnx2*) ; 
 scalar_t__ BNX2_CHIP_5709 ; 
 int BNX2_L2CTX_CMD_TYPE ; 
 int BNX2_L2CTX_CMD_TYPE_TYPE_L2 ; 
 int BNX2_L2CTX_CMD_TYPE_XI ; 
 int BNX2_L2CTX_TBDR_BHADDR_HI ; 
 int BNX2_L2CTX_TBDR_BHADDR_HI_XI ; 
 int BNX2_L2CTX_TBDR_BHADDR_LO ; 
 int BNX2_L2CTX_TBDR_BHADDR_LO_XI ; 
 int BNX2_L2CTX_TYPE ; 
 int BNX2_L2CTX_TYPE_SIZE_L2 ; 
 int BNX2_L2CTX_TYPE_TYPE_L2 ; 
 int BNX2_L2CTX_TYPE_XI ; 
 int GET_CID_ADDR (int) ; 
 int /*<<< orphan*/  bnx2_ctx_wr (struct bnx2*,int,int,int) ; 

__attribute__((used)) static void
bnx2_init_tx_context(struct bnx2 *bp, u32 cid, struct bnx2_tx_ring_info *txr)
{
	u32 val, offset0, offset1, offset2, offset3;
	u32 cid_addr = GET_CID_ADDR(cid);

	if (BNX2_CHIP(bp) == BNX2_CHIP_5709) {
		offset0 = BNX2_L2CTX_TYPE_XI;
		offset1 = BNX2_L2CTX_CMD_TYPE_XI;
		offset2 = BNX2_L2CTX_TBDR_BHADDR_HI_XI;
		offset3 = BNX2_L2CTX_TBDR_BHADDR_LO_XI;
	} else {
		offset0 = BNX2_L2CTX_TYPE;
		offset1 = BNX2_L2CTX_CMD_TYPE;
		offset2 = BNX2_L2CTX_TBDR_BHADDR_HI;
		offset3 = BNX2_L2CTX_TBDR_BHADDR_LO;
	}
	val = BNX2_L2CTX_TYPE_TYPE_L2 | BNX2_L2CTX_TYPE_SIZE_L2;
	bnx2_ctx_wr(bp, cid_addr, offset0, val);

	val = BNX2_L2CTX_CMD_TYPE_TYPE_L2 | (8 << 16);
	bnx2_ctx_wr(bp, cid_addr, offset1, val);

	val = (u64) txr->tx_desc_mapping >> 32;
	bnx2_ctx_wr(bp, cid_addr, offset2, val);

	val = (u64) txr->tx_desc_mapping & 0xffffffff;
	bnx2_ctx_wr(bp, cid_addr, offset3, val);
}