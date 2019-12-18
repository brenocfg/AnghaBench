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
struct ppa_addr {int dummy; } ;
struct pblk_line {TYPE_1__* w_err_gc; int /*<<< orphan*/  id; struct pblk_emeta* emeta; } ;
struct pblk_g_ctx {struct pblk_line* private; } ;
struct pblk_emeta {int nr_entries; int /*<<< orphan*/  sync; } ;
struct pblk {int /*<<< orphan*/  inflight_io; int /*<<< orphan*/  close_wq; } ;
struct nvm_rq {int /*<<< orphan*/  nr_ppas; scalar_t__ error; struct pblk* private; } ;
struct TYPE_2__ {int has_write_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PBLK_WRITE_INT ; 
 int atomic_add_return (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 struct pblk_g_ctx* nvm_rq_to_pdu (struct nvm_rq*) ; 
 struct ppa_addr* nvm_rq_to_ppa_list (struct nvm_rq*) ; 
 int /*<<< orphan*/  pblk_check_chunk_state_update (struct pblk*,struct nvm_rq*) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_free_rqd (struct pblk*,struct nvm_rq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_gen_run_ws (struct pblk*,struct pblk_line*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_line_close_ws ; 
 int /*<<< orphan*/  pblk_log_write_err (struct pblk*,struct nvm_rq*) ; 
 int /*<<< orphan*/  pblk_up_chunk (struct pblk*,struct ppa_addr) ; 
 scalar_t__ trace_pblk_chunk_state_enabled () ; 

__attribute__((used)) static void pblk_end_io_write_meta(struct nvm_rq *rqd)
{
	struct pblk *pblk = rqd->private;
	struct pblk_g_ctx *m_ctx = nvm_rq_to_pdu(rqd);
	struct pblk_line *line = m_ctx->private;
	struct pblk_emeta *emeta = line->emeta;
	struct ppa_addr *ppa_list = nvm_rq_to_ppa_list(rqd);
	int sync;

	pblk_up_chunk(pblk, ppa_list[0]);

	if (rqd->error) {
		pblk_log_write_err(pblk, rqd);
		pblk_err(pblk, "metadata I/O failed. Line %d\n", line->id);
		line->w_err_gc->has_write_err = 1;
	} else {
		if (trace_pblk_chunk_state_enabled())
			pblk_check_chunk_state_update(pblk, rqd);
	}

	sync = atomic_add_return(rqd->nr_ppas, &emeta->sync);
	if (sync == emeta->nr_entries)
		pblk_gen_run_ws(pblk, line, NULL, pblk_line_close_ws,
						GFP_ATOMIC, pblk->close_wq);

	pblk_free_rqd(pblk, rqd, PBLK_WRITE_INT);

	atomic_dec(&pblk->inflight_io);
}