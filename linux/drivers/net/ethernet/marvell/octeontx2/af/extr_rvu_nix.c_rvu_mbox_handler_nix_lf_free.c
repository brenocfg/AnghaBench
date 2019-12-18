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
struct rvu_pfvf {int /*<<< orphan*/  nixlf; } ;
struct rvu_hwinfo {struct rvu_block* block; } ;
struct rvu_block {scalar_t__ addr; } ;
struct rvu {int /*<<< orphan*/  dev; struct rvu_hwinfo* hw; } ;
struct msg_rsp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcifunc; } ;
struct msg_req {TYPE_1__ hdr; } ;

/* Variables and functions */
 scalar_t__ BLKADDR_NIX0 ; 
 int /*<<< orphan*/  BLKTYPE_NIX ; 
 int NIX_AF_ERR_AF_LF_INVALID ; 
 int NIX_AF_ERR_LF_RESET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  nix_ctx_free (struct rvu*,struct rvu_pfvf*) ; 
 int /*<<< orphan*/  nix_interface_deinit (struct rvu*,int /*<<< orphan*/ ,int) ; 
 int rvu_get_blkaddr (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rvu_get_lf (struct rvu*,struct rvu_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rvu_pfvf* rvu_get_pfvf (struct rvu*,int /*<<< orphan*/ ) ; 
 int rvu_lf_reset (struct rvu*,struct rvu_block*,int) ; 

int rvu_mbox_handler_nix_lf_free(struct rvu *rvu, struct msg_req *req,
				 struct msg_rsp *rsp)
{
	struct rvu_hwinfo *hw = rvu->hw;
	u16 pcifunc = req->hdr.pcifunc;
	struct rvu_block *block;
	int blkaddr, nixlf, err;
	struct rvu_pfvf *pfvf;

	pfvf = rvu_get_pfvf(rvu, pcifunc);
	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, pcifunc);
	if (!pfvf->nixlf || blkaddr < 0)
		return NIX_AF_ERR_AF_LF_INVALID;

	block = &hw->block[blkaddr];
	nixlf = rvu_get_lf(rvu, block, pcifunc, 0);
	if (nixlf < 0)
		return NIX_AF_ERR_AF_LF_INVALID;

	nix_interface_deinit(rvu, pcifunc, nixlf);

	/* Reset this NIX LF */
	err = rvu_lf_reset(rvu, block, nixlf);
	if (err) {
		dev_err(rvu->dev, "Failed to reset NIX%d LF%d\n",
			block->addr - BLKADDR_NIX0, nixlf);
		return NIX_AF_ERR_LF_RESET;
	}

	nix_ctx_free(rvu, pfvf);

	return 0;
}