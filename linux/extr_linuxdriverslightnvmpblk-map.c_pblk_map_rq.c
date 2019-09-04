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
struct pblk_sec_meta {int dummy; } ;
struct pblk {int min_write_pgs; } ;
struct nvm_rq {int nr_ppas; int /*<<< orphan*/  bio; int /*<<< orphan*/ * ppa_list; struct pblk_sec_meta* meta_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  PBLK_WRITE ; 
 int /*<<< orphan*/  bio_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_free_rqd (struct pblk*,struct nvm_rq*,int /*<<< orphan*/ ) ; 
 scalar_t__ pblk_map_page_data (struct pblk*,unsigned int,int /*<<< orphan*/ *,unsigned long*,struct pblk_sec_meta*,unsigned int) ; 
 int /*<<< orphan*/  pblk_pipeline_stop (struct pblk*) ; 

void pblk_map_rq(struct pblk *pblk, struct nvm_rq *rqd, unsigned int sentry,
		 unsigned long *lun_bitmap, unsigned int valid_secs,
		 unsigned int off)
{
	struct pblk_sec_meta *meta_list = rqd->meta_list;
	unsigned int map_secs;
	int min = pblk->min_write_pgs;
	int i;

	for (i = off; i < rqd->nr_ppas; i += min) {
		map_secs = (i + min > valid_secs) ? (valid_secs % min) : min;
		if (pblk_map_page_data(pblk, sentry + i, &rqd->ppa_list[i],
					lun_bitmap, &meta_list[i], map_secs)) {
			bio_put(rqd->bio);
			pblk_free_rqd(pblk, rqd, PBLK_WRITE);
			pblk_pipeline_stop(pblk);
		}
	}
}