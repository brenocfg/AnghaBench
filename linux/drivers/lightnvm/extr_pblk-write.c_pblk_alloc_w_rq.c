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
struct pblk {int dummy; } ;
struct nvm_rq {unsigned int nr_ppas; int is_seq; int /*<<< orphan*/ * end_io; struct pblk* private; int /*<<< orphan*/  opcode; } ;
typedef  int /*<<< orphan*/  nvm_end_io_fn ;

/* Variables and functions */
 int /*<<< orphan*/  NVM_OP_PWRITE ; 
 int pblk_alloc_rqd_meta (struct pblk*,struct nvm_rq*) ; 

__attribute__((used)) static int pblk_alloc_w_rq(struct pblk *pblk, struct nvm_rq *rqd,
			   unsigned int nr_secs, nvm_end_io_fn(*end_io))
{
	/* Setup write request */
	rqd->opcode = NVM_OP_PWRITE;
	rqd->nr_ppas = nr_secs;
	rqd->is_seq = 1;
	rqd->private = pblk;
	rqd->end_io = end_io;

	return pblk_alloc_rqd_meta(pblk, rqd);
}