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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct rvu {TYPE_1__* hw; } ;
struct npc_mcam {int total_entries; int banksize; } ;
struct nix_rx_action {int index; int flow_key_alg; int /*<<< orphan*/  pf_func; int /*<<< orphan*/  op; } ;
struct TYPE_2__ {struct npc_mcam mcam; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKTYPE_NPC ; 
 int DEFAULT_RSS_CONTEXT_GROUP ; 
 int /*<<< orphan*/  NIXLF_PROMISC_ENTRY ; 
 int /*<<< orphan*/  NIXLF_UCAST_ENTRY ; 
 int /*<<< orphan*/  NIX_RX_ACTIONOP_RSS ; 
 int /*<<< orphan*/  NPC_AF_MCAMEX_BANKX_ACTION (int,int) ; 
 scalar_t__ is_mcam_entry_enabled (struct rvu*,struct npc_mcam*,int,int) ; 
 int npc_get_bank (struct npc_mcam*,int) ; 
 int npc_get_nixlf_mcam_index (struct npc_mcam*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int rvu_get_blkaddr (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvu_npc_update_rxvlan (struct rvu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rvu_read64 (struct rvu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rvu_npc_update_flowkey_alg_idx(struct rvu *rvu, u16 pcifunc, int nixlf,
				    int group, int alg_idx, int mcam_index)
{
	struct npc_mcam *mcam = &rvu->hw->mcam;
	struct nix_rx_action action;
	int blkaddr, index, bank;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	if (blkaddr < 0)
		return;

	/* Check if this is for reserved default entry */
	if (mcam_index < 0) {
		if (group != DEFAULT_RSS_CONTEXT_GROUP)
			return;
		index = npc_get_nixlf_mcam_index(mcam, pcifunc,
						 nixlf, NIXLF_UCAST_ENTRY);
	} else {
		/* TODO: validate this mcam index */
		index = mcam_index;
	}

	if (index >= mcam->total_entries)
		return;

	bank = npc_get_bank(mcam, index);
	index &= (mcam->banksize - 1);

	*(u64 *)&action = rvu_read64(rvu, blkaddr,
				     NPC_AF_MCAMEX_BANKX_ACTION(index, bank));
	/* Ignore if no action was set earlier */
	if (!*(u64 *)&action)
		return;

	action.op = NIX_RX_ACTIONOP_RSS;
	action.pf_func = pcifunc;
	action.index = group;
	action.flow_key_alg = alg_idx;

	rvu_write64(rvu, blkaddr,
		    NPC_AF_MCAMEX_BANKX_ACTION(index, bank), *(u64 *)&action);

	index = npc_get_nixlf_mcam_index(mcam, pcifunc,
					 nixlf, NIXLF_PROMISC_ENTRY);

	/* If PF's promiscuous entry is enabled,
	 * Set RSS action for that entry as well
	 */
	if (is_mcam_entry_enabled(rvu, mcam, blkaddr, index)) {
		bank = npc_get_bank(mcam, index);
		index &= (mcam->banksize - 1);

		rvu_write64(rvu, blkaddr,
			    NPC_AF_MCAMEX_BANKX_ACTION(index, bank),
			    *(u64 *)&action);
	}

	rvu_npc_update_rxvlan(rvu, pcifunc, nixlf);
}