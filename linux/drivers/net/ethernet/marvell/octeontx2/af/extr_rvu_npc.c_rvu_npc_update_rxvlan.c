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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int /*<<< orphan*/  action; } ;
struct rvu_pfvf {TYPE_2__ entry; int /*<<< orphan*/  rxvlan_index; int /*<<< orphan*/  rxvlan; } ;
struct rvu {TYPE_1__* hw; } ;
struct npc_mcam {int dummy; } ;
struct TYPE_3__ {struct npc_mcam mcam; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKTYPE_NPC ; 
 int /*<<< orphan*/  NIXLF_UCAST_ENTRY ; 
 int NIX_AF_ERR_AF_LF_INVALID ; 
 int /*<<< orphan*/  NIX_INTF_RX ; 
 int is_mcam_entry_enabled (struct rvu*,struct npc_mcam*,int,int) ; 
 int /*<<< orphan*/  npc_config_mcam_entry (struct rvu*,struct npc_mcam*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  npc_get_mcam_action (struct rvu*,struct npc_mcam*,int,int) ; 
 int npc_get_nixlf_mcam_index (struct npc_mcam*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int rvu_get_blkaddr (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rvu_pfvf* rvu_get_pfvf (struct rvu*,int /*<<< orphan*/ ) ; 

int rvu_npc_update_rxvlan(struct rvu *rvu, u16 pcifunc, int nixlf)
{
	struct rvu_pfvf *pfvf = rvu_get_pfvf(rvu, pcifunc);
	struct npc_mcam *mcam = &rvu->hw->mcam;
	int blkaddr, index;
	bool enable;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	if (blkaddr < 0)
		return NIX_AF_ERR_AF_LF_INVALID;

	if (!pfvf->rxvlan)
		return 0;

	index = npc_get_nixlf_mcam_index(mcam, pcifunc, nixlf,
					 NIXLF_UCAST_ENTRY);
	pfvf->entry.action = npc_get_mcam_action(rvu, mcam, blkaddr, index);
	enable = is_mcam_entry_enabled(rvu, mcam, blkaddr, index);
	npc_config_mcam_entry(rvu, mcam, blkaddr, pfvf->rxvlan_index,
			      NIX_INTF_RX, &pfvf->entry, enable);

	return 0;
}