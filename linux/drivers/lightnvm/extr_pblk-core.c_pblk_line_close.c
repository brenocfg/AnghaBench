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
struct pblk_lun {int /*<<< orphan*/  bppa; } ;
struct pblk_line_mgmt {int /*<<< orphan*/  gc_lock; int /*<<< orphan*/  bitmap_pool; int /*<<< orphan*/  free_lock; int /*<<< orphan*/  meta_bitmap; } ;
struct pblk_line_meta {int blk_per_line; int /*<<< orphan*/  sec_per_line; } ;
struct pblk_line {scalar_t__ state; int /*<<< orphan*/  id; int /*<<< orphan*/  lock; TYPE_1__* chks; int /*<<< orphan*/ * emeta; int /*<<< orphan*/ * smeta; int /*<<< orphan*/ * map_bitmap; int /*<<< orphan*/  list; int /*<<< orphan*/  meta_line; } ;
struct pblk {struct pblk_lun* luns; struct pblk_line_mgmt l_mg; struct pblk_line_meta lm; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int dummy; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {int state; } ;

/* Variables and functions */
 int NVM_CHK_ST_CLOSED ; 
 int NVM_CHK_ST_OFFLINE ; 
 scalar_t__ PBLK_LINESTATE_CLOSED ; 
 scalar_t__ PBLK_LINESTATE_OPEN ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bitmap_full (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  mempool_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_disk_name (struct pblk*) ; 
 struct list_head* pblk_line_gc_list (struct pblk*,struct pblk_line*) ; 
 int pblk_ppa_to_pos (struct nvm_geo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_pblk_line_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void pblk_line_close(struct pblk *pblk, struct pblk_line *line)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	struct pblk_line_meta *lm = &pblk->lm;
	struct pblk_line_mgmt *l_mg = &pblk->l_mg;
	struct list_head *move_list;
	int i;

#ifdef CONFIG_NVM_PBLK_DEBUG
	WARN(!bitmap_full(line->map_bitmap, lm->sec_per_line),
				"pblk: corrupt closed line %d\n", line->id);
#endif

	spin_lock(&l_mg->free_lock);
	WARN_ON(!test_and_clear_bit(line->meta_line, &l_mg->meta_bitmap));
	spin_unlock(&l_mg->free_lock);

	spin_lock(&l_mg->gc_lock);
	spin_lock(&line->lock);
	WARN_ON(line->state != PBLK_LINESTATE_OPEN);
	line->state = PBLK_LINESTATE_CLOSED;
	move_list = pblk_line_gc_list(pblk, line);
	list_add_tail(&line->list, move_list);

	mempool_free(line->map_bitmap, l_mg->bitmap_pool);
	line->map_bitmap = NULL;
	line->smeta = NULL;
	line->emeta = NULL;

	for (i = 0; i < lm->blk_per_line; i++) {
		struct pblk_lun *rlun = &pblk->luns[i];
		int pos = pblk_ppa_to_pos(geo, rlun->bppa);
		int state = line->chks[pos].state;

		if (!(state & NVM_CHK_ST_OFFLINE))
			state = NVM_CHK_ST_CLOSED;
	}

	spin_unlock(&line->lock);
	spin_unlock(&l_mg->gc_lock);

	trace_pblk_line_state(pblk_disk_name(pblk), line->id,
					line->state);
}