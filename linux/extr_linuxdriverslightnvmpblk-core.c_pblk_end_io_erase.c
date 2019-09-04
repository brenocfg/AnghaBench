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
struct pblk {int /*<<< orphan*/  e_rq_pool; } ;
struct nvm_rq {struct pblk* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pblk_end_io_erase (struct pblk*,struct nvm_rq*) ; 
 int /*<<< orphan*/  mempool_free (struct nvm_rq*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pblk_end_io_erase(struct nvm_rq *rqd)
{
	struct pblk *pblk = rqd->private;

	__pblk_end_io_erase(pblk, rqd);
	mempool_free(rqd, &pblk->e_rq_pool);
}