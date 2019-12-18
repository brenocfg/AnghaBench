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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct rvu {int /*<<< orphan*/  rsrc_lock; int /*<<< orphan*/  hw; } ;
struct nix_hw {TYPE_1__* txsch; } ;
struct TYPE_2__ {int /*<<< orphan*/ * pfvf_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKTYPE_NIX ; 
 int EINVAL ; 
 int NIX_AF_ERR_AF_LF_INVALID ; 
 int NIX_AF_TL1X_CIR (int) ; 
 int NIX_AF_TL1X_SCHEDULE (int) ; 
 int NIX_AF_TL1X_TOPOLOGY (int) ; 
 int NIX_TXSCHQ_TL1_CFG_DONE ; 
 size_t NIX_TXSCH_LVL_TL1 ; 
 int /*<<< orphan*/  TXSCH_MAP (int,int) ; 
 int TXSCH_MAP_FLAGS (int /*<<< orphan*/ ) ; 
 int TXSCH_MAP_FUNC (int /*<<< orphan*/ ) ; 
 int TXSCH_TL1_DFLT_RR_PRIO ; 
 int TXSCH_TL1_DFLT_RR_QTM ; 
 struct nix_hw* get_nix_hw (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rvu_get_blkaddr (struct rvu*,int /*<<< orphan*/ ,int) ; 
 int rvu_get_tl1_schqs (struct rvu*,int,int,int*,int*) ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int,int,int) ; 

__attribute__((used)) static int
nix_tl1_default_cfg(struct rvu *rvu, u16 pcifunc)
{
	u16 schq_list[2], schq_cnt, schq;
	int blkaddr, idx, err = 0;
	u16 map_func, map_flags;
	struct nix_hw *nix_hw;
	u64 reg, regval;
	u32 *pfvf_map;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, pcifunc);
	if (blkaddr < 0)
		return NIX_AF_ERR_AF_LF_INVALID;

	nix_hw = get_nix_hw(rvu->hw, blkaddr);
	if (!nix_hw)
		return -EINVAL;

	pfvf_map = nix_hw->txsch[NIX_TXSCH_LVL_TL1].pfvf_map;

	mutex_lock(&rvu->rsrc_lock);

	err = rvu_get_tl1_schqs(rvu, blkaddr,
				pcifunc, schq_list, &schq_cnt);
	if (err)
		goto unlock;

	for (idx = 0; idx < schq_cnt; idx++) {
		schq = schq_list[idx];
		map_func = TXSCH_MAP_FUNC(pfvf_map[schq]);
		map_flags = TXSCH_MAP_FLAGS(pfvf_map[schq]);

		/* check if config is already done or this is pf */
		if (map_flags & NIX_TXSCHQ_TL1_CFG_DONE)
			continue;

		/* default configuration */
		reg = NIX_AF_TL1X_TOPOLOGY(schq);
		regval = (TXSCH_TL1_DFLT_RR_PRIO << 1);
		rvu_write64(rvu, blkaddr, reg, regval);
		reg = NIX_AF_TL1X_SCHEDULE(schq);
		regval = TXSCH_TL1_DFLT_RR_QTM;
		rvu_write64(rvu, blkaddr, reg, regval);
		reg = NIX_AF_TL1X_CIR(schq);
		regval = 0;
		rvu_write64(rvu, blkaddr, reg, regval);

		map_flags |= NIX_TXSCHQ_TL1_CFG_DONE;
		pfvf_map[schq] = TXSCH_MAP(map_func, map_flags);
	}
unlock:
	mutex_unlock(&rvu->rsrc_lock);
	return err;
}