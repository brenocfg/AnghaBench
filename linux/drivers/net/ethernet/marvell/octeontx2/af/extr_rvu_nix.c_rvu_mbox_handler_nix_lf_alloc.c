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
typedef  void* u16 ;
struct rvu_pfvf {int /*<<< orphan*/  tx_chan_cnt; int /*<<< orphan*/  rx_chan_cnt; int /*<<< orphan*/  tx_chan_base; int /*<<< orphan*/  rx_chan_base; int /*<<< orphan*/  mac_addr; TYPE_2__* nix_qints_ctx; TYPE_2__* cq_ints_ctx; TYPE_2__* cq_ctx; void* cq_bmap; TYPE_2__* sq_ctx; void* sq_bmap; TYPE_2__* rq_ctx; void* rq_bmap; int /*<<< orphan*/  nixlf; } ;
struct rvu_hwinfo {struct rvu_block* block; } ;
struct rvu_block {scalar_t__ addr; } ;
struct rvu {int /*<<< orphan*/  dev; struct rvu_hwinfo* hw; } ;
struct nix_lf_alloc_rsp {int sqb_size; int lf_rx_stats; int lf_tx_stats; int qints; int cints; int /*<<< orphan*/  lso_tsov6_idx; int /*<<< orphan*/  lso_tsov4_idx; int /*<<< orphan*/  tx_chan_cnt; int /*<<< orphan*/  rx_chan_cnt; int /*<<< orphan*/  tx_chan_base; int /*<<< orphan*/  rx_chan_base; int /*<<< orphan*/  mac_addr; } ;
struct TYPE_3__ {void* pcifunc; } ;
struct nix_lf_alloc_req {int rq_cnt; int sq_cnt; int cq_cnt; int npa_func; scalar_t__ sso_func; int rx_cfg; scalar_t__ xqe_sz; int /*<<< orphan*/  rss_grps; int /*<<< orphan*/  rss_sz; TYPE_1__ hdr; } ;
struct TYPE_4__ {scalar_t__ iova; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 scalar_t__ BLKADDR_NIX0 ; 
 int /*<<< orphan*/  BLKTYPE_NIX ; 
 int /*<<< orphan*/  BLKTYPE_NPA ; 
 int /*<<< orphan*/  BLKTYPE_SSO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_RSS_GROUPS ; 
 int /*<<< orphan*/  MAX_RSS_INDIR_TBL_SIZE ; 
 int /*<<< orphan*/  NIX_AF_CONST1 ; 
 int /*<<< orphan*/  NIX_AF_CONST2 ; 
 int /*<<< orphan*/  NIX_AF_CONST3 ; 
 int NIX_AF_ERR_AF_LF_INVALID ; 
 int NIX_AF_ERR_LF_RESET ; 
 int NIX_AF_ERR_PARAM ; 
 int NIX_AF_ERR_RSS_GRPS_INVALID ; 
 int NIX_AF_ERR_RSS_SIZE_INVALID ; 
 int NIX_AF_INVAL_NPA_PF_FUNC ; 
 int NIX_AF_INVAL_SSO_PF_FUNC ; 
 int /*<<< orphan*/  NIX_AF_LFX_CFG (int) ; 
 int /*<<< orphan*/  NIX_AF_LFX_CINTS_BASE (int) ; 
 int /*<<< orphan*/  NIX_AF_LFX_CINTS_CFG (int) ; 
 int /*<<< orphan*/  NIX_AF_LFX_CQS_BASE (int) ; 
 int /*<<< orphan*/  NIX_AF_LFX_CQS_CFG (int) ; 
 int /*<<< orphan*/  NIX_AF_LFX_QINTS_BASE (int) ; 
 int /*<<< orphan*/  NIX_AF_LFX_QINTS_CFG (int) ; 
 int /*<<< orphan*/  NIX_AF_LFX_RQS_BASE (int) ; 
 int /*<<< orphan*/  NIX_AF_LFX_RQS_CFG (int) ; 
 int /*<<< orphan*/  NIX_AF_LFX_RX_CFG (int) ; 
 int /*<<< orphan*/  NIX_AF_LFX_SQS_BASE (int) ; 
 int /*<<< orphan*/  NIX_AF_LFX_SQS_CFG (int) ; 
 int /*<<< orphan*/  NIX_AF_LFX_TX_CFG (int) ; 
 int /*<<< orphan*/  NIX_AF_LFX_TX_CFG2 (int) ; 
 int /*<<< orphan*/  NIX_AF_SQ_CONST ; 
 int NIX_INTF_TYPE_CGX ; 
 int NIX_INTF_TYPE_LBK ; 
 int /*<<< orphan*/  NIX_LSO_FORMAT_IDX_TSOV4 ; 
 int /*<<< orphan*/  NIX_LSO_FORMAT_IDX_TSOV6 ; 
 scalar_t__ RVU_DEFAULT_PF_FUNC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_afvf (void*) ; 
 int /*<<< orphan*/  is_pffunc_map_valid (struct rvu*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_power_of_2 (int /*<<< orphan*/ ) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nix_ctx_free (struct rvu*,struct rvu_pfvf*) ; 
 int nix_interface_init (struct rvu*,void*,int,int) ; 
 int nixlf_rss_ctx_init (struct rvu*,int,struct rvu_pfvf*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qmem_alloc (int /*<<< orphan*/ ,TYPE_2__**,int,int) ; 
 int rvu_get_blkaddr (struct rvu*,int /*<<< orphan*/ ,void*) ; 
 int rvu_get_lf (struct rvu*,struct rvu_block*,void*,int /*<<< orphan*/ ) ; 
 struct rvu_pfvf* rvu_get_pfvf (struct rvu*,void*) ; 
 int rvu_lf_reset (struct rvu*,struct rvu_block*,int) ; 
 int /*<<< orphan*/  rvu_npc_disable_default_entries (struct rvu*,void*,int) ; 
 int rvu_read64 (struct rvu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int,int /*<<< orphan*/ ,int) ; 

int rvu_mbox_handler_nix_lf_alloc(struct rvu *rvu,
				  struct nix_lf_alloc_req *req,
				  struct nix_lf_alloc_rsp *rsp)
{
	int nixlf, qints, hwctx_size, intf, err, rc = 0;
	struct rvu_hwinfo *hw = rvu->hw;
	u16 pcifunc = req->hdr.pcifunc;
	struct rvu_block *block;
	struct rvu_pfvf *pfvf;
	u64 cfg, ctx_cfg;
	int blkaddr;

	if (!req->rq_cnt || !req->sq_cnt || !req->cq_cnt)
		return NIX_AF_ERR_PARAM;

	pfvf = rvu_get_pfvf(rvu, pcifunc);
	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, pcifunc);
	if (!pfvf->nixlf || blkaddr < 0)
		return NIX_AF_ERR_AF_LF_INVALID;

	block = &hw->block[blkaddr];
	nixlf = rvu_get_lf(rvu, block, pcifunc, 0);
	if (nixlf < 0)
		return NIX_AF_ERR_AF_LF_INVALID;

	/* Check if requested 'NIXLF <=> NPALF' mapping is valid */
	if (req->npa_func) {
		/* If default, use 'this' NIXLF's PFFUNC */
		if (req->npa_func == RVU_DEFAULT_PF_FUNC)
			req->npa_func = pcifunc;
		if (!is_pffunc_map_valid(rvu, req->npa_func, BLKTYPE_NPA))
			return NIX_AF_INVAL_NPA_PF_FUNC;
	}

	/* Check if requested 'NIXLF <=> SSOLF' mapping is valid */
	if (req->sso_func) {
		/* If default, use 'this' NIXLF's PFFUNC */
		if (req->sso_func == RVU_DEFAULT_PF_FUNC)
			req->sso_func = pcifunc;
		if (!is_pffunc_map_valid(rvu, req->sso_func, BLKTYPE_SSO))
			return NIX_AF_INVAL_SSO_PF_FUNC;
	}

	/* If RSS is being enabled, check if requested config is valid.
	 * RSS table size should be power of two, otherwise
	 * RSS_GRP::OFFSET + adder might go beyond that group or
	 * won't be able to use entire table.
	 */
	if (req->rss_sz && (req->rss_sz > MAX_RSS_INDIR_TBL_SIZE ||
			    !is_power_of_2(req->rss_sz)))
		return NIX_AF_ERR_RSS_SIZE_INVALID;

	if (req->rss_sz &&
	    (!req->rss_grps || req->rss_grps > MAX_RSS_GROUPS))
		return NIX_AF_ERR_RSS_GRPS_INVALID;

	/* Reset this NIX LF */
	err = rvu_lf_reset(rvu, block, nixlf);
	if (err) {
		dev_err(rvu->dev, "Failed to reset NIX%d LF%d\n",
			block->addr - BLKADDR_NIX0, nixlf);
		return NIX_AF_ERR_LF_RESET;
	}

	ctx_cfg = rvu_read64(rvu, blkaddr, NIX_AF_CONST3);

	/* Alloc NIX RQ HW context memory and config the base */
	hwctx_size = 1UL << ((ctx_cfg >> 4) & 0xF);
	err = qmem_alloc(rvu->dev, &pfvf->rq_ctx, req->rq_cnt, hwctx_size);
	if (err)
		goto free_mem;

	pfvf->rq_bmap = kcalloc(req->rq_cnt, sizeof(long), GFP_KERNEL);
	if (!pfvf->rq_bmap)
		goto free_mem;

	rvu_write64(rvu, blkaddr, NIX_AF_LFX_RQS_BASE(nixlf),
		    (u64)pfvf->rq_ctx->iova);

	/* Set caching and queue count in HW */
	cfg = BIT_ULL(36) | (req->rq_cnt - 1);
	rvu_write64(rvu, blkaddr, NIX_AF_LFX_RQS_CFG(nixlf), cfg);

	/* Alloc NIX SQ HW context memory and config the base */
	hwctx_size = 1UL << (ctx_cfg & 0xF);
	err = qmem_alloc(rvu->dev, &pfvf->sq_ctx, req->sq_cnt, hwctx_size);
	if (err)
		goto free_mem;

	pfvf->sq_bmap = kcalloc(req->sq_cnt, sizeof(long), GFP_KERNEL);
	if (!pfvf->sq_bmap)
		goto free_mem;

	rvu_write64(rvu, blkaddr, NIX_AF_LFX_SQS_BASE(nixlf),
		    (u64)pfvf->sq_ctx->iova);
	cfg = BIT_ULL(36) | (req->sq_cnt - 1);
	rvu_write64(rvu, blkaddr, NIX_AF_LFX_SQS_CFG(nixlf), cfg);

	/* Alloc NIX CQ HW context memory and config the base */
	hwctx_size = 1UL << ((ctx_cfg >> 8) & 0xF);
	err = qmem_alloc(rvu->dev, &pfvf->cq_ctx, req->cq_cnt, hwctx_size);
	if (err)
		goto free_mem;

	pfvf->cq_bmap = kcalloc(req->cq_cnt, sizeof(long), GFP_KERNEL);
	if (!pfvf->cq_bmap)
		goto free_mem;

	rvu_write64(rvu, blkaddr, NIX_AF_LFX_CQS_BASE(nixlf),
		    (u64)pfvf->cq_ctx->iova);
	cfg = BIT_ULL(36) | (req->cq_cnt - 1);
	rvu_write64(rvu, blkaddr, NIX_AF_LFX_CQS_CFG(nixlf), cfg);

	/* Initialize receive side scaling (RSS) */
	hwctx_size = 1UL << ((ctx_cfg >> 12) & 0xF);
	err = nixlf_rss_ctx_init(rvu, blkaddr, pfvf, nixlf,
				 req->rss_sz, req->rss_grps, hwctx_size);
	if (err)
		goto free_mem;

	/* Alloc memory for CQINT's HW contexts */
	cfg = rvu_read64(rvu, blkaddr, NIX_AF_CONST2);
	qints = (cfg >> 24) & 0xFFF;
	hwctx_size = 1UL << ((ctx_cfg >> 24) & 0xF);
	err = qmem_alloc(rvu->dev, &pfvf->cq_ints_ctx, qints, hwctx_size);
	if (err)
		goto free_mem;

	rvu_write64(rvu, blkaddr, NIX_AF_LFX_CINTS_BASE(nixlf),
		    (u64)pfvf->cq_ints_ctx->iova);
	rvu_write64(rvu, blkaddr, NIX_AF_LFX_CINTS_CFG(nixlf), BIT_ULL(36));

	/* Alloc memory for QINT's HW contexts */
	cfg = rvu_read64(rvu, blkaddr, NIX_AF_CONST2);
	qints = (cfg >> 12) & 0xFFF;
	hwctx_size = 1UL << ((ctx_cfg >> 20) & 0xF);
	err = qmem_alloc(rvu->dev, &pfvf->nix_qints_ctx, qints, hwctx_size);
	if (err)
		goto free_mem;

	rvu_write64(rvu, blkaddr, NIX_AF_LFX_QINTS_BASE(nixlf),
		    (u64)pfvf->nix_qints_ctx->iova);
	rvu_write64(rvu, blkaddr, NIX_AF_LFX_QINTS_CFG(nixlf), BIT_ULL(36));

	/* Setup VLANX TPID's.
	 * Use VLAN1 for 802.1Q
	 * and VLAN0 for 802.1AD.
	 */
	cfg = (0x8100ULL << 16) | 0x88A8ULL;
	rvu_write64(rvu, blkaddr, NIX_AF_LFX_TX_CFG(nixlf), cfg);

	/* Enable LMTST for this NIX LF */
	rvu_write64(rvu, blkaddr, NIX_AF_LFX_TX_CFG2(nixlf), BIT_ULL(0));

	/* Set CQE/WQE size, NPA_PF_FUNC for SQBs and also SSO_PF_FUNC */
	if (req->npa_func)
		cfg = req->npa_func;
	if (req->sso_func)
		cfg |= (u64)req->sso_func << 16;

	cfg |= (u64)req->xqe_sz << 33;
	rvu_write64(rvu, blkaddr, NIX_AF_LFX_CFG(nixlf), cfg);

	/* Config Rx pkt length, csum checks and apad  enable / disable */
	rvu_write64(rvu, blkaddr, NIX_AF_LFX_RX_CFG(nixlf), req->rx_cfg);

	intf = is_afvf(pcifunc) ? NIX_INTF_TYPE_LBK : NIX_INTF_TYPE_CGX;
	err = nix_interface_init(rvu, pcifunc, intf, nixlf);
	if (err)
		goto free_mem;

	/* Disable NPC entries as NIXLF's contexts are not initialized yet */
	rvu_npc_disable_default_entries(rvu, pcifunc, nixlf);

	goto exit;

free_mem:
	nix_ctx_free(rvu, pfvf);
	rc = -ENOMEM;

exit:
	/* Set macaddr of this PF/VF */
	ether_addr_copy(rsp->mac_addr, pfvf->mac_addr);

	/* set SQB size info */
	cfg = rvu_read64(rvu, blkaddr, NIX_AF_SQ_CONST);
	rsp->sqb_size = (cfg >> 34) & 0xFFFF;
	rsp->rx_chan_base = pfvf->rx_chan_base;
	rsp->tx_chan_base = pfvf->tx_chan_base;
	rsp->rx_chan_cnt = pfvf->rx_chan_cnt;
	rsp->tx_chan_cnt = pfvf->tx_chan_cnt;
	rsp->lso_tsov4_idx = NIX_LSO_FORMAT_IDX_TSOV4;
	rsp->lso_tsov6_idx = NIX_LSO_FORMAT_IDX_TSOV6;
	/* Get HW supported stat count */
	cfg = rvu_read64(rvu, blkaddr, NIX_AF_CONST1);
	rsp->lf_rx_stats = ((cfg >> 32) & 0xFF);
	rsp->lf_tx_stats = ((cfg >> 24) & 0xFF);
	/* Get count of CQ IRQs and error IRQs supported per LF */
	cfg = rvu_read64(rvu, blkaddr, NIX_AF_CONST2);
	rsp->qints = ((cfg >> 12) & 0xFFF);
	rsp->cints = ((cfg >> 24) & 0xFFF);
	return rc;
}