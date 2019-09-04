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
struct wa_counters {void* gc; void* pad; void* user; } ;
struct pblk_line_mgmt {int /*<<< orphan*/  close_lock; int /*<<< orphan*/  emeta_list; int /*<<< orphan*/  vsc_list; } ;
struct pblk_line_meta {int /*<<< orphan*/  blk_bitmap_len; int /*<<< orphan*/  vsc_list_len; } ;
struct pblk_line {scalar_t__ emeta_ssec; scalar_t__ cur_sec; int /*<<< orphan*/  lock; int /*<<< orphan*/  list; int /*<<< orphan*/  nr_valid_lbas; int /*<<< orphan*/  blk_bitmap; struct pblk_emeta* emeta; } ;
struct pblk_emeta {struct line_emeta* buf; } ;
struct pblk {int /*<<< orphan*/  gc_wa; int /*<<< orphan*/  pad_wa; int /*<<< orphan*/  user_wa; struct pblk_line_meta lm; struct pblk_line_mgmt l_mg; } ;
struct line_emeta {int /*<<< orphan*/  crc; void* nr_valid_lbas; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emeta_to_bb (struct line_emeta*) ; 
 int /*<<< orphan*/  emeta_to_vsc (struct pblk*,struct line_emeta*) ; 
 struct wa_counters* emeta_to_wa (struct pblk_line_meta*,struct line_emeta*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_calc_emeta_crc (struct pblk*,struct line_emeta*) ; 
 int /*<<< orphan*/  pblk_line_should_sync_meta (struct pblk*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void pblk_line_close_meta(struct pblk *pblk, struct pblk_line *line)
{
	struct pblk_line_mgmt *l_mg = &pblk->l_mg;
	struct pblk_line_meta *lm = &pblk->lm;
	struct pblk_emeta *emeta = line->emeta;
	struct line_emeta *emeta_buf = emeta->buf;
	struct wa_counters *wa = emeta_to_wa(lm, emeta_buf);

	/* No need for exact vsc value; avoid a big line lock and take aprox. */
	memcpy(emeta_to_vsc(pblk, emeta_buf), l_mg->vsc_list, lm->vsc_list_len);
	memcpy(emeta_to_bb(emeta_buf), line->blk_bitmap, lm->blk_bitmap_len);

	wa->user = cpu_to_le64(atomic64_read(&pblk->user_wa));
	wa->pad = cpu_to_le64(atomic64_read(&pblk->pad_wa));
	wa->gc = cpu_to_le64(atomic64_read(&pblk->gc_wa));

	emeta_buf->nr_valid_lbas = cpu_to_le64(line->nr_valid_lbas);
	emeta_buf->crc = cpu_to_le32(pblk_calc_emeta_crc(pblk, emeta_buf));

	spin_lock(&l_mg->close_lock);
	spin_lock(&line->lock);

	/* Update the in-memory start address for emeta, in case it has
	 * shifted due to write errors
	 */
	if (line->emeta_ssec != line->cur_sec)
		line->emeta_ssec = line->cur_sec;

	list_add_tail(&line->list, &l_mg->emeta_list);
	spin_unlock(&line->lock);
	spin_unlock(&l_mg->close_lock);

	pblk_line_should_sync_meta(pblk);


}