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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct rvu_pfvf {int /*<<< orphan*/  entry; } ;
struct rvu {TYPE_1__* hw; } ;
struct npc_mcam {int dummy; } ;
struct nix_rx_action {int /*<<< orphan*/  pf_func; int /*<<< orphan*/  op; } ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
struct mcam_entry {int* kw; int* kw_mask; int action; int vtag_action; TYPE_2__ member_0; } ;
typedef  int /*<<< orphan*/  entry ;
struct TYPE_3__ {struct npc_mcam mcam; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int /*<<< orphan*/  BLKTYPE_NPC ; 
 int ETH_ALEN ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NIXLF_UCAST_ENTRY ; 
 int /*<<< orphan*/  NIX_INTF_RX ; 
 int /*<<< orphan*/  NIX_RX_ACTIONOP_UCAST ; 
 int NPC_LID_LA ; 
 int NPC_LT_LB_CTAG ; 
 int NPC_LT_LB_STAG ; 
 int NPC_PARSE_RESULT_DMAC_OFFSET ; 
 int /*<<< orphan*/  VTAG0_LID_MASK ; 
 int /*<<< orphan*/  VTAG0_RELPTR_MASK ; 
 int /*<<< orphan*/  VTAG0_TYPE_MASK ; 
 int VTAG0_VALID_BIT ; 
 scalar_t__ is_afvf (int /*<<< orphan*/ ) ; 
 scalar_t__ is_mcam_entry_enabled (struct rvu*,struct npc_mcam*,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mcam_entry*,int) ; 
 int /*<<< orphan*/  npc_config_mcam_entry (struct rvu*,struct npc_mcam*,int,int,int /*<<< orphan*/ ,struct mcam_entry*,int) ; 
 int npc_get_mcam_action (struct rvu*,struct npc_mcam*,int,int) ; 
 int npc_get_nixlf_mcam_index (struct npc_mcam*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int rvu_get_blkaddr (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rvu_pfvf* rvu_get_pfvf (struct rvu*,int /*<<< orphan*/ ) ; 

void rvu_npc_install_ucast_entry(struct rvu *rvu, u16 pcifunc,
				 int nixlf, u64 chan, u8 *mac_addr)
{
	struct rvu_pfvf *pfvf = rvu_get_pfvf(rvu, pcifunc);
	struct npc_mcam *mcam = &rvu->hw->mcam;
	struct mcam_entry entry = { {0} };
	struct nix_rx_action action;
	int blkaddr, index, kwi;
	u64 mac = 0;

	/* AF's VFs work in promiscuous mode */
	if (is_afvf(pcifunc))
		return;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	if (blkaddr < 0)
		return;

	for (index = ETH_ALEN - 1; index >= 0; index--)
		mac |= ((u64)*mac_addr++) << (8 * index);

	index = npc_get_nixlf_mcam_index(mcam, pcifunc,
					 nixlf, NIXLF_UCAST_ENTRY);

	/* Match ingress channel and DMAC */
	entry.kw[0] = chan;
	entry.kw_mask[0] = 0xFFFULL;

	kwi = NPC_PARSE_RESULT_DMAC_OFFSET / sizeof(u64);
	entry.kw[kwi] = mac;
	entry.kw_mask[kwi] = BIT_ULL(48) - 1;

	/* Don't change the action if entry is already enabled
	 * Otherwise RSS action may get overwritten.
	 */
	if (is_mcam_entry_enabled(rvu, mcam, blkaddr, index)) {
		*(u64 *)&action = npc_get_mcam_action(rvu, mcam,
						      blkaddr, index);
	} else {
		*(u64 *)&action = 0x00;
		action.op = NIX_RX_ACTIONOP_UCAST;
		action.pf_func = pcifunc;
	}

	entry.action = *(u64 *)&action;
	npc_config_mcam_entry(rvu, mcam, blkaddr, index,
			      NIX_INTF_RX, &entry, true);

	/* add VLAN matching, setup action and save entry back for later */
	entry.kw[0] |= (NPC_LT_LB_STAG | NPC_LT_LB_CTAG) << 20;
	entry.kw_mask[0] |= (NPC_LT_LB_STAG & NPC_LT_LB_CTAG) << 20;

	entry.vtag_action = VTAG0_VALID_BIT |
			    FIELD_PREP(VTAG0_TYPE_MASK, 0) |
			    FIELD_PREP(VTAG0_LID_MASK, NPC_LID_LA) |
			    FIELD_PREP(VTAG0_RELPTR_MASK, 12);

	memcpy(&pfvf->entry, &entry, sizeof(entry));
}