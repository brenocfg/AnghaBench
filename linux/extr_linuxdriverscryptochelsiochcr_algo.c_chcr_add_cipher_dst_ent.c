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
struct dsgl_walk {int /*<<< orphan*/  last_sg_len; int /*<<< orphan*/  last_sg; } ;
struct crypto_ablkcipher {int dummy; } ;
struct cpl_rx_phys_dsgl {int dummy; } ;
struct cipher_wr_param {int /*<<< orphan*/  bytes; int /*<<< orphan*/  req; } ;
struct chcr_context {int /*<<< orphan*/  pci_chan_id; } ;
struct chcr_blkcipher_req_ctx {int /*<<< orphan*/  dst_ofst; int /*<<< orphan*/  dstsg; } ;
struct ablkcipher_request {int dummy; } ;

/* Variables and functions */
 struct chcr_blkcipher_req_ctx* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 struct chcr_context* c_ctx (struct crypto_ablkcipher*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsgl_walk_add_sg (struct dsgl_walk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsgl_walk_end (struct dsgl_walk*,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsgl_walk_init (struct dsgl_walk*,struct cpl_rx_phys_dsgl*) ; 

void chcr_add_cipher_dst_ent(struct ablkcipher_request *req,
			     struct cpl_rx_phys_dsgl *phys_cpl,
			     struct  cipher_wr_param *wrparam,
			     unsigned short qid)
{
	struct chcr_blkcipher_req_ctx *reqctx = ablkcipher_request_ctx(req);
	struct crypto_ablkcipher *tfm = crypto_ablkcipher_reqtfm(wrparam->req);
	struct chcr_context *ctx = c_ctx(tfm);
	struct dsgl_walk dsgl_walk;

	dsgl_walk_init(&dsgl_walk, phys_cpl);
	dsgl_walk_add_sg(&dsgl_walk, reqctx->dstsg, wrparam->bytes,
			 reqctx->dst_ofst);
	reqctx->dstsg = dsgl_walk.last_sg;
	reqctx->dst_ofst = dsgl_walk.last_sg_len;

	dsgl_walk_end(&dsgl_walk, qid, ctx->pci_chan_id);
}