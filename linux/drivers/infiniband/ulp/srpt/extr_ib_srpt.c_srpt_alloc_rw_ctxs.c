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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct srpt_rw_ctx {unsigned int nents; struct scatterlist* sg; int /*<<< orphan*/  rw; } ;
struct srpt_send_ioctx {int n_rw_ctx; int n_rdma; struct srpt_rw_ctx* rw_ctxs; struct srpt_rw_ctx s_rw_ctx; struct srpt_rdma_ch* ch; int /*<<< orphan*/  cmd; } ;
struct srpt_rdma_ch {TYPE_1__* sport; int /*<<< orphan*/  qp; } ;
struct srp_direct_buf {int /*<<< orphan*/  key; int /*<<< orphan*/  len; int /*<<< orphan*/  va; } ;
struct scatterlist {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct srpt_rw_ctx*) ; 
 struct srpt_rw_ctx* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_rw_ctx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct scatterlist*,unsigned int,int) ; 
 int rdma_rw_ctx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct scatterlist*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_chain (struct scatterlist*,unsigned int,struct scatterlist*) ; 
 int /*<<< orphan*/  sg_unmark_end (struct scatterlist*) ; 
 int target_alloc_sgl (struct scatterlist**,unsigned int*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  target_free_sgl (struct scatterlist*,unsigned int) ; 
 int target_reverse_dma_direction (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int srpt_alloc_rw_ctxs(struct srpt_send_ioctx *ioctx,
		struct srp_direct_buf *db, int nbufs, struct scatterlist **sg,
		unsigned *sg_cnt)
{
	enum dma_data_direction dir = target_reverse_dma_direction(&ioctx->cmd);
	struct srpt_rdma_ch *ch = ioctx->ch;
	struct scatterlist *prev = NULL;
	unsigned prev_nents;
	int ret, i;

	if (nbufs == 1) {
		ioctx->rw_ctxs = &ioctx->s_rw_ctx;
	} else {
		ioctx->rw_ctxs = kmalloc_array(nbufs, sizeof(*ioctx->rw_ctxs),
			GFP_KERNEL);
		if (!ioctx->rw_ctxs)
			return -ENOMEM;
	}

	for (i = ioctx->n_rw_ctx; i < nbufs; i++, db++) {
		struct srpt_rw_ctx *ctx = &ioctx->rw_ctxs[i];
		u64 remote_addr = be64_to_cpu(db->va);
		u32 size = be32_to_cpu(db->len);
		u32 rkey = be32_to_cpu(db->key);

		ret = target_alloc_sgl(&ctx->sg, &ctx->nents, size, false,
				i < nbufs - 1);
		if (ret)
			goto unwind;

		ret = rdma_rw_ctx_init(&ctx->rw, ch->qp, ch->sport->port,
				ctx->sg, ctx->nents, 0, remote_addr, rkey, dir);
		if (ret < 0) {
			target_free_sgl(ctx->sg, ctx->nents);
			goto unwind;
		}

		ioctx->n_rdma += ret;
		ioctx->n_rw_ctx++;

		if (prev) {
			sg_unmark_end(&prev[prev_nents - 1]);
			sg_chain(prev, prev_nents + 1, ctx->sg);
		} else {
			*sg = ctx->sg;
		}

		prev = ctx->sg;
		prev_nents = ctx->nents;

		*sg_cnt += ctx->nents;
	}

	return 0;

unwind:
	while (--i >= 0) {
		struct srpt_rw_ctx *ctx = &ioctx->rw_ctxs[i];

		rdma_rw_ctx_destroy(&ctx->rw, ch->qp, ch->sport->port,
				ctx->sg, ctx->nents, dir);
		target_free_sgl(ctx->sg, ctx->nents);
	}
	if (ioctx->rw_ctxs != &ioctx->s_rw_ctx)
		kfree(ioctx->rw_ctxs);
	return ret;
}