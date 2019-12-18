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
struct TYPE_2__ {int /*<<< orphan*/  pcifunc; } ;
struct nix_vtag_config {scalar_t__ cfg_type; TYPE_1__ hdr; } ;
struct msg_rsp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKTYPE_NIX ; 
 int NIX_AF_ERR_AF_LF_INVALID ; 
 int NIX_AF_ERR_PARAM ; 
 int nix_rx_vtag_cfg (struct rvu*,int,int,struct nix_vtag_config*) ; 
 int rvu_get_blkaddr (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rvu_get_lf (struct rvu*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rvu_mbox_handler_nix_vtag_cfg(struct rvu *rvu,
				  struct nix_vtag_config *req,
				  struct msg_rsp *rsp)
{
	struct rvu_hwinfo *hw = rvu->hw;
	u16 pcifunc = req->hdr.pcifunc;
	int blkaddr, nixlf, err;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, pcifunc);
	if (blkaddr < 0)
		return NIX_AF_ERR_AF_LF_INVALID;

	nixlf = rvu_get_lf(rvu, &hw->block[blkaddr], pcifunc, 0);
	if (nixlf < 0)
		return NIX_AF_ERR_AF_LF_INVALID;

	if (req->cfg_type) {
		err = nix_rx_vtag_cfg(rvu, nixlf, blkaddr, req);
		if (err)
			return NIX_AF_ERR_PARAM;
	} else {
		/* TODO: handle tx vtag configuration */
		return 0;
	}

	return 0;
}