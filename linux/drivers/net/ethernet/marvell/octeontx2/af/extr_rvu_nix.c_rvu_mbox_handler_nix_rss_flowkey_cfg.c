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
typedef  int /*<<< orphan*/  u16 ;
struct rvu_hwinfo {int /*<<< orphan*/ * block; } ;
struct rvu {struct rvu_hwinfo* hw; } ;
struct nix_rss_flowkey_cfg_rsp {int alg_idx; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcifunc; } ;
struct nix_rss_flowkey_cfg {int /*<<< orphan*/  mcam_index; int /*<<< orphan*/  group; int /*<<< orphan*/  flowkey_cfg; TYPE_1__ hdr; } ;
struct nix_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKTYPE_NIX ; 
 int EINVAL ; 
 int NIX_AF_ERR_AF_LF_INVALID ; 
 int get_flowkey_alg_idx (struct nix_hw*,int /*<<< orphan*/ ) ; 
 struct nix_hw* get_nix_hw (struct rvu_hwinfo*,int) ; 
 int reserve_flowkey_alg_idx (struct rvu*,int,int /*<<< orphan*/ ) ; 
 int rvu_get_blkaddr (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rvu_get_lf (struct rvu*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvu_npc_update_flowkey_alg_idx (struct rvu*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int rvu_mbox_handler_nix_rss_flowkey_cfg(struct rvu *rvu,
					 struct nix_rss_flowkey_cfg *req,
					 struct nix_rss_flowkey_cfg_rsp *rsp)
{
	struct rvu_hwinfo *hw = rvu->hw;
	u16 pcifunc = req->hdr.pcifunc;
	int alg_idx, nixlf, blkaddr;
	struct nix_hw *nix_hw;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, pcifunc);
	if (blkaddr < 0)
		return NIX_AF_ERR_AF_LF_INVALID;

	nixlf = rvu_get_lf(rvu, &hw->block[blkaddr], pcifunc, 0);
	if (nixlf < 0)
		return NIX_AF_ERR_AF_LF_INVALID;

	nix_hw = get_nix_hw(rvu->hw, blkaddr);
	if (!nix_hw)
		return -EINVAL;

	alg_idx = get_flowkey_alg_idx(nix_hw, req->flowkey_cfg);
	/* Failed to get algo index from the exiting list, reserve new  */
	if (alg_idx < 0) {
		alg_idx = reserve_flowkey_alg_idx(rvu, blkaddr,
						  req->flowkey_cfg);
		if (alg_idx < 0)
			return alg_idx;
	}
	rsp->alg_idx = alg_idx;
	rvu_npc_update_flowkey_alg_idx(rvu, pcifunc, nixlf, req->group,
				       alg_idx, req->mcam_index);
	return 0;
}