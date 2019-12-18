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
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct rvu_pfvf {int /*<<< orphan*/  nixlf; } ;
struct rvu {int /*<<< orphan*/  rsrc_lock; int /*<<< orphan*/  hw; } ;
struct nix_txsch_alloc_rsp {int* schq_contig; int* schq; size_t** schq_list; size_t** schq_contig_list; } ;
struct TYPE_2__ {size_t pcifunc; } ;
struct nix_txsch_alloc_req {int* schq_contig; int* schq; TYPE_1__ hdr; } ;
struct nix_txsch {int /*<<< orphan*/  schq; int /*<<< orphan*/ * pfvf_map; } ;
struct nix_hw {struct nix_txsch* txsch; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKTYPE_NIX ; 
 int EINVAL ; 
 int MAX_TXSCHQ_PER_FUNC ; 
 int NIX_AF_ERR_AF_LF_INVALID ; 
 int NIX_AF_ERR_TLX_ALLOC_FAIL ; 
 int NIX_TXSCH_LVL_CNT ; 
 int NIX_TXSCH_LVL_TL1 ; 
 int /*<<< orphan*/  TXSCH_MAP (size_t,int /*<<< orphan*/ ) ; 
 struct nix_hw* get_nix_hw (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nix_reset_tx_linkcfg (struct rvu*,int,int,size_t) ; 
 int /*<<< orphan*/  nix_reset_tx_shaping (struct rvu*,int,int,size_t) ; 
 size_t rvu_alloc_rsrc (int /*<<< orphan*/ *) ; 
 size_t rvu_alloc_rsrc_contig (int /*<<< orphan*/ *,int) ; 
 int rvu_get_blkaddr (struct rvu*,int /*<<< orphan*/ ,size_t) ; 
 struct rvu_pfvf* rvu_get_pfvf (struct rvu*,size_t) ; 
 scalar_t__ rvu_get_tl1_schqs (struct rvu*,int,size_t,size_t*,int*) ; 
 int /*<<< orphan*/  rvu_rsrc_check_contig (int /*<<< orphan*/ *,int) ; 
 int rvu_rsrc_free_count (int /*<<< orphan*/ *) ; 

int rvu_mbox_handler_nix_txsch_alloc(struct rvu *rvu,
				     struct nix_txsch_alloc_req *req,
				     struct nix_txsch_alloc_rsp *rsp)
{
	u16 pcifunc = req->hdr.pcifunc;
	struct nix_txsch *txsch;
	int lvl, idx, req_schq;
	struct rvu_pfvf *pfvf;
	struct nix_hw *nix_hw;
	int blkaddr, rc = 0;
	u32 *pfvf_map;
	u16 schq;

	pfvf = rvu_get_pfvf(rvu, pcifunc);
	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, pcifunc);
	if (!pfvf->nixlf || blkaddr < 0)
		return NIX_AF_ERR_AF_LF_INVALID;

	nix_hw = get_nix_hw(rvu->hw, blkaddr);
	if (!nix_hw)
		return -EINVAL;

	mutex_lock(&rvu->rsrc_lock);
	for (lvl = 0; lvl < NIX_TXSCH_LVL_CNT; lvl++) {
		txsch = &nix_hw->txsch[lvl];
		req_schq = req->schq_contig[lvl] + req->schq[lvl];
		pfvf_map = txsch->pfvf_map;

		if (!req_schq)
			continue;

		/* There are only 28 TL1s */
		if (lvl == NIX_TXSCH_LVL_TL1) {
			if (req->schq_contig[lvl] ||
			    req->schq[lvl] > 2 ||
			    rvu_get_tl1_schqs(rvu, blkaddr,
					      pcifunc, NULL, NULL))
				goto err;
			continue;
		}

		/* Check if request is valid */
		if (req_schq > MAX_TXSCHQ_PER_FUNC)
			goto err;

		/* If contiguous queues are needed, check for availability */
		if (req->schq_contig[lvl] &&
		    !rvu_rsrc_check_contig(&txsch->schq, req->schq_contig[lvl]))
			goto err;

		/* Check if full request can be accommodated */
		if (req_schq >= rvu_rsrc_free_count(&txsch->schq))
			goto err;
	}

	for (lvl = 0; lvl < NIX_TXSCH_LVL_CNT; lvl++) {
		txsch = &nix_hw->txsch[lvl];
		rsp->schq_contig[lvl] = req->schq_contig[lvl];
		pfvf_map = txsch->pfvf_map;
		rsp->schq[lvl] = req->schq[lvl];

		if (!req->schq[lvl] && !req->schq_contig[lvl])
			continue;

		/* Handle TL1 specially as it is
		 * allocation is restricted to 2 TL1's
		 * per link
		 */

		if (lvl == NIX_TXSCH_LVL_TL1) {
			rsp->schq_contig[lvl] = 0;
			rvu_get_tl1_schqs(rvu, blkaddr, pcifunc,
					  &rsp->schq_list[lvl][0],
					  &rsp->schq[lvl]);
			continue;
		}

		/* Alloc contiguous queues first */
		if (req->schq_contig[lvl]) {
			schq = rvu_alloc_rsrc_contig(&txsch->schq,
						     req->schq_contig[lvl]);

			for (idx = 0; idx < req->schq_contig[lvl]; idx++) {
				pfvf_map[schq] = TXSCH_MAP(pcifunc, 0);
				nix_reset_tx_linkcfg(rvu, blkaddr, lvl, schq);
				nix_reset_tx_shaping(rvu, blkaddr, lvl, schq);
				rsp->schq_contig_list[lvl][idx] = schq;
				schq++;
			}
		}

		/* Alloc non-contiguous queues */
		for (idx = 0; idx < req->schq[lvl]; idx++) {
			schq = rvu_alloc_rsrc(&txsch->schq);
			pfvf_map[schq] = TXSCH_MAP(pcifunc, 0);
			nix_reset_tx_linkcfg(rvu, blkaddr, lvl, schq);
			nix_reset_tx_shaping(rvu, blkaddr, lvl, schq);
			rsp->schq_list[lvl][idx] = schq;
		}
	}
	goto exit;
err:
	rc = NIX_AF_ERR_TLX_ALLOC_FAIL;
exit:
	mutex_unlock(&rvu->rsrc_lock);
	return rc;
}