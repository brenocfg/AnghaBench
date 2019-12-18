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
struct ppa_addr {int dummy; } ;
struct pblk_pad_rq {int /*<<< orphan*/  ref; struct pblk* pblk; } ;
struct pblk {int /*<<< orphan*/  inflight_io; } ;
struct nvm_rq {struct pblk_pad_rq* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  PBLK_WRITE_INT ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ppa_addr* nvm_rq_to_ppa_list (struct nvm_rq*) ; 
 int /*<<< orphan*/  pblk_free_rqd (struct pblk*,struct nvm_rq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_recov_complete ; 
 int /*<<< orphan*/  pblk_up_chunk (struct pblk*,struct ppa_addr) ; 

__attribute__((used)) static void pblk_end_io_recov(struct nvm_rq *rqd)
{
	struct ppa_addr *ppa_list = nvm_rq_to_ppa_list(rqd);
	struct pblk_pad_rq *pad_rq = rqd->private;
	struct pblk *pblk = pad_rq->pblk;

	pblk_up_chunk(pblk, ppa_list[0]);

	pblk_free_rqd(pblk, rqd, PBLK_WRITE_INT);

	atomic_dec(&pblk->inflight_io);
	kref_put(&pad_rq->ref, pblk_recov_complete);
}