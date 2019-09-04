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
struct pblk_line {int /*<<< orphan*/  ref; } ;
struct pblk {struct pblk_line* lines; } ;
struct nvm_rq {int nr_ppas; struct ppa_addr ppa_addr; struct ppa_addr* ppa_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_line_put_wq ; 
 size_t pblk_ppa_to_line (struct ppa_addr) ; 

__attribute__((used)) static void pblk_read_put_rqd_kref(struct pblk *pblk, struct nvm_rq *rqd)
{
	struct ppa_addr *ppa_list;
	int i;

	ppa_list = (rqd->nr_ppas > 1) ? rqd->ppa_list : &rqd->ppa_addr;

	for (i = 0; i < rqd->nr_ppas; i++) {
		struct ppa_addr ppa = ppa_list[i];
		struct pblk_line *line;

		line = &pblk->lines[pblk_ppa_to_line(ppa)];
		kref_put(&line->ref, pblk_line_put_wq);
	}
}