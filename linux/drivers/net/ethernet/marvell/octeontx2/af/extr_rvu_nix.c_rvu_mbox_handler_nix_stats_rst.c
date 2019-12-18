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
typedef  int /*<<< orphan*/  u16 ;
struct rvu_hwinfo {int /*<<< orphan*/ * block; } ;
struct rvu {struct rvu_hwinfo* hw; } ;
struct msg_rsp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcifunc; } ;
struct msg_req {TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKTYPE_NIX ; 
 int /*<<< orphan*/  NIX_AF_CONST1 ; 
 int NIX_AF_ERR_AF_LF_INVALID ; 
 int /*<<< orphan*/  NIX_AF_LFX_RX_STATX (int,int) ; 
 int /*<<< orphan*/  NIX_AF_LFX_TX_STATX (int,int) ; 
 int rvu_get_blkaddr (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rvu_get_lf (struct rvu*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rvu_read64 (struct rvu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rvu_mbox_handler_nix_stats_rst(struct rvu *rvu, struct msg_req *req,
				   struct msg_rsp *rsp)
{
	struct rvu_hwinfo *hw = rvu->hw;
	u16 pcifunc = req->hdr.pcifunc;
	int i, nixlf, blkaddr;
	u64 stats;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, pcifunc);
	if (blkaddr < 0)
		return NIX_AF_ERR_AF_LF_INVALID;

	nixlf = rvu_get_lf(rvu, &hw->block[blkaddr], pcifunc, 0);
	if (nixlf < 0)
		return NIX_AF_ERR_AF_LF_INVALID;

	/* Get stats count supported by HW */
	stats = rvu_read64(rvu, blkaddr, NIX_AF_CONST1);

	/* Reset tx stats */
	for (i = 0; i < ((stats >> 24) & 0xFF); i++)
		rvu_write64(rvu, blkaddr, NIX_AF_LFX_TX_STATX(nixlf, i), 0);

	/* Reset rx stats */
	for (i = 0; i < ((stats >> 32) & 0xFF); i++)
		rvu_write64(rvu, blkaddr, NIX_AF_LFX_RX_STATX(nixlf, i), 0);

	return 0;
}