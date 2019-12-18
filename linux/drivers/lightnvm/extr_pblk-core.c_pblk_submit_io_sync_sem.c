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
struct pblk {int dummy; } ;
struct nvm_rq {int dummy; } ;

/* Variables and functions */
 struct ppa_addr* nvm_rq_to_ppa_list (struct nvm_rq*) ; 
 int /*<<< orphan*/  pblk_down_chunk (struct pblk*,struct ppa_addr) ; 
 int pblk_submit_io_sync (struct pblk*,struct nvm_rq*,void*) ; 
 int /*<<< orphan*/  pblk_up_chunk (struct pblk*,struct ppa_addr) ; 

__attribute__((used)) static int pblk_submit_io_sync_sem(struct pblk *pblk, struct nvm_rq *rqd,
				   void *buf)
{
	struct ppa_addr *ppa_list = nvm_rq_to_ppa_list(rqd);
	int ret;

	pblk_down_chunk(pblk, ppa_list[0]);
	ret = pblk_submit_io_sync(pblk, rqd, buf);
	pblk_up_chunk(pblk, ppa_list[0]);

	return ret;
}