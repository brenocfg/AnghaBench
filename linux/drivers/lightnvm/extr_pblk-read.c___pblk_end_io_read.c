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
struct pblk_g_ctx {unsigned long start_time; int /*<<< orphan*/  lba; } ;
struct pblk {int /*<<< orphan*/  inflight_io; int /*<<< orphan*/  inflight_reads; int /*<<< orphan*/  sync_reads; TYPE_1__* disk; struct nvm_tgt_dev* dev; } ;
struct nvm_tgt_dev {int /*<<< orphan*/  q; } ;
struct nvm_rq {int /*<<< orphan*/  nr_ppas; scalar_t__ error; struct bio* bio; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  part0; } ;

/* Variables and functions */
 int /*<<< orphan*/  PBLK_READ ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  generic_end_io_acct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 struct pblk_g_ctx* nvm_rq_to_pdu (struct nvm_rq*) ; 
 int /*<<< orphan*/  pblk_free_rqd (struct pblk*,struct nvm_rq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_log_read_err (struct pblk*,struct nvm_rq*) ; 
 int /*<<< orphan*/  pblk_read_check_seq (struct pblk*,struct nvm_rq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_rq_to_line_put (struct pblk*,struct nvm_rq*) ; 

__attribute__((used)) static void __pblk_end_io_read(struct pblk *pblk, struct nvm_rq *rqd,
			       bool put_line)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct pblk_g_ctx *r_ctx = nvm_rq_to_pdu(rqd);
	struct bio *int_bio = rqd->bio;
	unsigned long start_time = r_ctx->start_time;

	generic_end_io_acct(dev->q, REQ_OP_READ, &pblk->disk->part0, start_time);

	if (rqd->error)
		pblk_log_read_err(pblk, rqd);

	pblk_read_check_seq(pblk, rqd, r_ctx->lba);
	bio_put(int_bio);

	if (put_line)
		pblk_rq_to_line_put(pblk, rqd);

#ifdef CONFIG_NVM_PBLK_DEBUG
	atomic_long_add(rqd->nr_ppas, &pblk->sync_reads);
	atomic_long_sub(rqd->nr_ppas, &pblk->inflight_reads);
#endif

	pblk_free_rqd(pblk, rqd, PBLK_READ);
	atomic_dec(&pblk->inflight_io);
}