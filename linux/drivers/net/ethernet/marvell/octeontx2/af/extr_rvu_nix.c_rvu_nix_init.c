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
struct rvu_hwinfo {int cgx; int lmac_per_cgx; int cgx_links; int lbk_links; int sdp_links; int /*<<< orphan*/  nix0; struct rvu_block* block; } ;
struct rvu_block {int dummy; } ;
struct rvu {int /*<<< orphan*/  dev; struct rvu_hwinfo* hw; } ;
struct nix_hw {int dummy; } ;

/* Variables and functions */
 int BLKADDR_NIX0 ; 
 int /*<<< orphan*/  BLKTYPE_NIX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NIX_AF_CFG ; 
 int /*<<< orphan*/  NIX_AF_CINT_DELAY ; 
 int /*<<< orphan*/  NIX_AF_CONST ; 
 int /*<<< orphan*/  NIX_AF_RX_DEF_IIP4 ; 
 int /*<<< orphan*/  NIX_AF_RX_DEF_IIP6 ; 
 int /*<<< orphan*/  NIX_AF_RX_DEF_ISCTP ; 
 int /*<<< orphan*/  NIX_AF_RX_DEF_ITCP ; 
 int /*<<< orphan*/  NIX_AF_RX_DEF_IUDP ; 
 int /*<<< orphan*/  NIX_AF_RX_DEF_OIP4 ; 
 int /*<<< orphan*/  NIX_AF_RX_DEF_OIP6 ; 
 int /*<<< orphan*/  NIX_AF_RX_DEF_OL2 ; 
 int /*<<< orphan*/  NIX_AF_RX_DEF_OSCTP ; 
 int /*<<< orphan*/  NIX_AF_RX_DEF_OTCP ; 
 int /*<<< orphan*/  NIX_AF_RX_DEF_OUDP ; 
 int NPC_LID_LA ; 
 int NPC_LID_LC ; 
 int NPC_LID_LD ; 
 int NPC_LID_LF ; 
 int NPC_LID_LG ; 
 int NPC_LT_LA_ETHER ; 
 int NPC_LT_LC_IP ; 
 int NPC_LT_LC_IP6 ; 
 int NPC_LT_LD_SCTP ; 
 int NPC_LT_LD_TCP ; 
 int NPC_LT_LD_UDP ; 
 int NPC_LT_LF_TU_IP ; 
 int NPC_LT_LF_TU_IP6 ; 
 int NPC_LT_LG_TU_SCTP ; 
 int NPC_LT_LG_TU_TCP ; 
 int NPC_LT_LG_TU_UDP ; 
 int /*<<< orphan*/  devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ is_rvu_9xxx_A0 (struct rvu*) ; 
 int nix_af_mark_format_setup (struct rvu*,int /*<<< orphan*/ ,int) ; 
 int nix_aq_init (struct rvu*,struct rvu_block*) ; 
 int nix_calibrate_x2p (struct rvu*,int) ; 
 int /*<<< orphan*/  nix_link_config (struct rvu*,int) ; 
 int nix_rx_flowkey_alg_cfg (struct rvu*,int) ; 
 int /*<<< orphan*/  nix_setup_lso (struct rvu*,int /*<<< orphan*/ ,int) ; 
 int nix_setup_mcast (struct rvu*,int /*<<< orphan*/ ,int) ; 
 int nix_setup_txschq (struct rvu*,int /*<<< orphan*/ ,int) ; 
 int rvu_get_blkaddr (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rvu_read64 (struct rvu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int,int /*<<< orphan*/ ,int) ; 

int rvu_nix_init(struct rvu *rvu)
{
	struct rvu_hwinfo *hw = rvu->hw;
	struct rvu_block *block;
	int blkaddr, err;
	u64 cfg;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, 0);
	if (blkaddr < 0)
		return 0;
	block = &hw->block[blkaddr];

	/* As per a HW errata in 9xxx A0 silicon, NIX may corrupt
	 * internal state when conditional clocks are turned off.
	 * Hence enable them.
	 */
	if (is_rvu_9xxx_A0(rvu))
		rvu_write64(rvu, blkaddr, NIX_AF_CFG,
			    rvu_read64(rvu, blkaddr, NIX_AF_CFG) | 0x5EULL);

	/* Calibrate X2P bus to check if CGX/LBK links are fine */
	err = nix_calibrate_x2p(rvu, blkaddr);
	if (err)
		return err;

	/* Set num of links of each type */
	cfg = rvu_read64(rvu, blkaddr, NIX_AF_CONST);
	hw->cgx = (cfg >> 12) & 0xF;
	hw->lmac_per_cgx = (cfg >> 8) & 0xF;
	hw->cgx_links = hw->cgx * hw->lmac_per_cgx;
	hw->lbk_links = 1;
	hw->sdp_links = 1;

	/* Initialize admin queue */
	err = nix_aq_init(rvu, block);
	if (err)
		return err;

	/* Restore CINT timer delay to HW reset values */
	rvu_write64(rvu, blkaddr, NIX_AF_CINT_DELAY, 0x0ULL);

	if (blkaddr == BLKADDR_NIX0) {
		hw->nix0 = devm_kzalloc(rvu->dev,
					sizeof(struct nix_hw), GFP_KERNEL);
		if (!hw->nix0)
			return -ENOMEM;

		err = nix_setup_txschq(rvu, hw->nix0, blkaddr);
		if (err)
			return err;

		err = nix_af_mark_format_setup(rvu, hw->nix0, blkaddr);
		if (err)
			return err;

		err = nix_setup_mcast(rvu, hw->nix0, blkaddr);
		if (err)
			return err;

		/* Configure segmentation offload formats */
		nix_setup_lso(rvu, hw->nix0, blkaddr);

		/* Config Outer/Inner L2, IP, TCP, UDP and SCTP NPC layer info.
		 * This helps HW protocol checker to identify headers
		 * and validate length and checksums.
		 */
		rvu_write64(rvu, blkaddr, NIX_AF_RX_DEF_OL2,
			    (NPC_LID_LA << 8) | (NPC_LT_LA_ETHER << 4) | 0x0F);
		rvu_write64(rvu, blkaddr, NIX_AF_RX_DEF_OIP4,
			    (NPC_LID_LC << 8) | (NPC_LT_LC_IP << 4) | 0x0F);
		rvu_write64(rvu, blkaddr, NIX_AF_RX_DEF_IIP4,
			    (NPC_LID_LF << 8) | (NPC_LT_LF_TU_IP << 4) | 0x0F);
		rvu_write64(rvu, blkaddr, NIX_AF_RX_DEF_OIP6,
			    (NPC_LID_LC << 8) | (NPC_LT_LC_IP6 << 4) | 0x0F);
		rvu_write64(rvu, blkaddr, NIX_AF_RX_DEF_IIP6,
			    (NPC_LID_LF << 8) | (NPC_LT_LF_TU_IP6 << 4) | 0x0F);
		rvu_write64(rvu, blkaddr, NIX_AF_RX_DEF_OTCP,
			    (NPC_LID_LD << 8) | (NPC_LT_LD_TCP << 4) | 0x0F);
		rvu_write64(rvu, blkaddr, NIX_AF_RX_DEF_ITCP,
			    (NPC_LID_LG << 8) | (NPC_LT_LG_TU_TCP << 4) | 0x0F);
		rvu_write64(rvu, blkaddr, NIX_AF_RX_DEF_OUDP,
			    (NPC_LID_LD << 8) | (NPC_LT_LD_UDP << 4) | 0x0F);
		rvu_write64(rvu, blkaddr, NIX_AF_RX_DEF_IUDP,
			    (NPC_LID_LG << 8) | (NPC_LT_LG_TU_UDP << 4) | 0x0F);
		rvu_write64(rvu, blkaddr, NIX_AF_RX_DEF_OSCTP,
			    (NPC_LID_LD << 8) | (NPC_LT_LD_SCTP << 4) | 0x0F);
		rvu_write64(rvu, blkaddr, NIX_AF_RX_DEF_ISCTP,
			    (NPC_LID_LG << 8) | (NPC_LT_LG_TU_SCTP << 4) |
			    0x0F);

		err = nix_rx_flowkey_alg_cfg(rvu, blkaddr);
		if (err)
			return err;

		/* Initialize CGX/LBK/SDP link credits, min/max pkt lengths */
		nix_link_config(rvu, blkaddr);
	}
	return 0;
}