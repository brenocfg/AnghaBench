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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct rvu_pfvf {int /*<<< orphan*/  cgx_lmac; } ;
struct rvu {int cgx_cnt_max; int /*<<< orphan*/  hw; } ;
struct TYPE_2__ {int max; } ;
struct nix_txsch {TYPE_1__ schq; scalar_t__* pfvf_map; } ;
struct nix_hw {struct nix_txsch* txsch; } ;

/* Variables and functions */
 int ENODEV ; 
 int MAX_LMAC_PER_CGX ; 
#define  NIX_INTF_TYPE_CGX 129 
#define  NIX_INTF_TYPE_LBK 128 
 size_t NIX_TXSCH_LVL_TL1 ; 
 int RVU_PFVF_PF_SHIFT ; 
 scalar_t__ TXSCH_MAP (int,int /*<<< orphan*/ ) ; 
 scalar_t__ U32_MAX ; 
 struct nix_hw* get_nix_hw (int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_afvf (int) ; 
 int /*<<< orphan*/  nix_reset_tx_linkcfg (struct rvu*,int,size_t,int) ; 
 int /*<<< orphan*/  nix_reset_tx_shaping (struct rvu*,int,size_t,int) ; 
 int /*<<< orphan*/  rvu_get_cgx_lmac_id (int /*<<< orphan*/ ,int*,int*) ; 
 int rvu_get_pf (int) ; 
 struct rvu_pfvf* rvu_get_pfvf (struct rvu*,int) ; 

__attribute__((used)) static int
rvu_get_tl1_schqs(struct rvu *rvu, int blkaddr, u16 pcifunc,
		  u16 *schq_list, u16 *schq_cnt)
{
	struct nix_txsch *txsch;
	struct nix_hw *nix_hw;
	struct rvu_pfvf *pfvf;
	u8 cgx_id, lmac_id;
	u16 schq_base;
	u32 *pfvf_map;
	int pf, intf;

	nix_hw = get_nix_hw(rvu->hw, blkaddr);
	if (!nix_hw)
		return -ENODEV;

	pfvf = rvu_get_pfvf(rvu, pcifunc);
	txsch = &nix_hw->txsch[NIX_TXSCH_LVL_TL1];
	pfvf_map = txsch->pfvf_map;
	pf = rvu_get_pf(pcifunc);

	/* static allocation as two TL1's per link */
	intf = is_afvf(pcifunc) ? NIX_INTF_TYPE_LBK : NIX_INTF_TYPE_CGX;

	switch (intf) {
	case NIX_INTF_TYPE_CGX:
		rvu_get_cgx_lmac_id(pfvf->cgx_lmac, &cgx_id, &lmac_id);
		schq_base = (cgx_id * MAX_LMAC_PER_CGX + lmac_id) * 2;
		break;
	case NIX_INTF_TYPE_LBK:
		schq_base = rvu->cgx_cnt_max * MAX_LMAC_PER_CGX * 2;
		break;
	default:
		return -ENODEV;
	}

	if (schq_base + 1 > txsch->schq.max)
		return -ENODEV;

	/* init pfvf_map as we store flags */
	if (pfvf_map[schq_base] == U32_MAX) {
		pfvf_map[schq_base] =
			TXSCH_MAP((pf << RVU_PFVF_PF_SHIFT), 0);
		pfvf_map[schq_base + 1] =
			TXSCH_MAP((pf << RVU_PFVF_PF_SHIFT), 0);

		/* Onetime reset for TL1 */
		nix_reset_tx_linkcfg(rvu, blkaddr,
				     NIX_TXSCH_LVL_TL1, schq_base);
		nix_reset_tx_shaping(rvu, blkaddr,
				     NIX_TXSCH_LVL_TL1, schq_base);

		nix_reset_tx_linkcfg(rvu, blkaddr,
				     NIX_TXSCH_LVL_TL1, schq_base + 1);
		nix_reset_tx_shaping(rvu, blkaddr,
				     NIX_TXSCH_LVL_TL1, schq_base + 1);
	}

	if (schq_list && schq_cnt) {
		schq_list[0] = schq_base;
		schq_list[1] = schq_base + 1;
		*schq_cnt = 2;
	}

	return 0;
}