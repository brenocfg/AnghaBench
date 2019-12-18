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
typedef  int u64 ;
typedef  int u16 ;
struct rvu_pfvf {int /*<<< orphan*/  bcast_mce_idx; } ;
struct rvu {TYPE_1__* hw; } ;
struct npc_mcam {int dummy; } ;
struct nix_rx_action {int pf_func; int /*<<< orphan*/  op; int /*<<< orphan*/  index; } ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
struct mcam_entry {int* kw; int* kw_mask; int action; TYPE_2__ member_0; } ;
struct TYPE_3__ {struct npc_mcam mcam; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int /*<<< orphan*/  BLKTYPE_NPC ; 
 int /*<<< orphan*/  NIXLF_BCAST_ENTRY ; 
 int /*<<< orphan*/  NIX_INTF_RX ; 
 int /*<<< orphan*/  NIX_RX_ACTIONOP_MCAST ; 
 int /*<<< orphan*/  NIX_RX_ACTIONOP_UCAST ; 
 int RVU_PFVF_FUNC_MASK ; 
 int /*<<< orphan*/  npc_config_mcam_entry (struct rvu*,struct npc_mcam*,int,int,int /*<<< orphan*/ ,struct mcam_entry*,int) ; 
 int npc_get_nixlf_mcam_index (struct npc_mcam*,int,int,int /*<<< orphan*/ ) ; 
 int rvu_get_blkaddr (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rvu_pfvf* rvu_get_pfvf (struct rvu*,int) ; 

void rvu_npc_install_bcast_match_entry(struct rvu *rvu, u16 pcifunc,
				       int nixlf, u64 chan)
{
	struct npc_mcam *mcam = &rvu->hw->mcam;
	struct mcam_entry entry = { {0} };
	struct nix_rx_action action;
#ifdef MCAST_MCE
	struct rvu_pfvf *pfvf;
#endif
	int blkaddr, index;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	if (blkaddr < 0)
		return;

	/* Only PF can add a bcast match entry */
	if (pcifunc & RVU_PFVF_FUNC_MASK)
		return;
#ifdef MCAST_MCE
	pfvf = rvu_get_pfvf(rvu, pcifunc & ~RVU_PFVF_FUNC_MASK);
#endif

	index = npc_get_nixlf_mcam_index(mcam, pcifunc,
					 nixlf, NIXLF_BCAST_ENTRY);

	/* Check for L2B bit and LMAC channel
	 * NOTE: Since MKEX default profile(a reduced version intended to
	 * accommodate more capability but igoring few bits) a stap-gap
	 * approach.
	 * Since we care for L2B which by HRM NPC_PARSE_KEX_S at BIT_POS[25], So
	 * moved to BIT_POS[13], ignoring ERRCODE, ERRLEV as we'll loose out
	 * on capability features needed for CoS (/from ODP PoV) e.g: VLAN,
	 * DSCP.
	 *
	 * Reduced layout of MKEX default profile -
	 * Includes following are (i.e.CHAN, L2/3{B/M}, LA, LB, LC, LD):
	 *
	 * BIT_POS[31:28] : LD
	 * BIT_POS[27:24] : LC
	 * BIT_POS[23:20] : LB
	 * BIT_POS[19:16] : LA
	 * BIT_POS[15:12] : L3B, L3M, L2B, L2M
	 * BIT_POS[11:00] : CHAN
	 *
	 */
	entry.kw[0] = BIT_ULL(13) | chan;
	entry.kw_mask[0] = BIT_ULL(13) | 0xFFFULL;

	*(u64 *)&action = 0x00;
#ifdef MCAST_MCE
	/* Early silicon doesn't support pkt replication,
	 * so install entry with UCAST action, so that PF
	 * receives all broadcast packets.
	 */
	action.op = NIX_RX_ACTIONOP_MCAST;
	action.pf_func = pcifunc;
	action.index = pfvf->bcast_mce_idx;
#else
	action.op = NIX_RX_ACTIONOP_UCAST;
	action.pf_func = pcifunc;
#endif

	entry.action = *(u64 *)&action;
	npc_config_mcam_entry(rvu, mcam, blkaddr, index,
			      NIX_INTF_RX, &entry, true);
}