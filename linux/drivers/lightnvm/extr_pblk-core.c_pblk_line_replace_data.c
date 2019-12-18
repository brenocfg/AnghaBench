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
struct pblk_line_mgmt {int /*<<< orphan*/  free_lock; struct pblk_line* data_next; int /*<<< orphan*/  d_seq_nr; struct pblk_line* data_line; } ;
struct pblk_line {int /*<<< orphan*/  type; scalar_t__ seq_nr; int /*<<< orphan*/  left_eblks; int /*<<< orphan*/  left_seblks; } ;
struct pblk {int /*<<< orphan*/  rl; int /*<<< orphan*/  lm; struct pblk_line_mgmt l_mg; } ;

/* Variables and functions */
 int /*<<< orphan*/  PBLK_LINETYPE_DATA ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_schedule () ; 
 scalar_t__ pblk_line_alloc_bitmaps (struct pblk*,struct pblk_line*) ; 
 scalar_t__ pblk_line_erase (struct pblk*,struct pblk_line*) ; 
 struct pblk_line* pblk_line_get (struct pblk*) ; 
 int /*<<< orphan*/  pblk_line_init_bb (struct pblk*,struct pblk_line*,int) ; 
 int /*<<< orphan*/  pblk_line_init_metadata (struct pblk*,struct pblk_line*,struct pblk_line*) ; 
 struct pblk_line* pblk_line_retry (struct pblk*,struct pblk_line*) ; 
 int /*<<< orphan*/  pblk_line_setup_metadata (struct pblk_line*,struct pblk_line_mgmt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pblk_rl_free_lines_dec (int /*<<< orphan*/ *,struct pblk_line*,int) ; 
 int /*<<< orphan*/  pblk_stop_writes (struct pblk*,struct pblk_line*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct pblk_line *pblk_line_replace_data(struct pblk *pblk)
{
	struct pblk_line_mgmt *l_mg = &pblk->l_mg;
	struct pblk_line *cur, *new = NULL;
	unsigned int left_seblks;

	new = l_mg->data_next;
	if (!new)
		goto out;

	spin_lock(&l_mg->free_lock);
	cur = l_mg->data_line;
	l_mg->data_line = new;

	pblk_line_setup_metadata(new, l_mg, &pblk->lm);
	spin_unlock(&l_mg->free_lock);

retry_erase:
	left_seblks = atomic_read(&new->left_seblks);
	if (left_seblks) {
		/* If line is not fully erased, erase it */
		if (atomic_read(&new->left_eblks)) {
			if (pblk_line_erase(pblk, new))
				goto out;
		} else {
			io_schedule();
		}
		goto retry_erase;
	}

	if (pblk_line_alloc_bitmaps(pblk, new))
		return NULL;

retry_setup:
	if (!pblk_line_init_metadata(pblk, new, cur)) {
		new = pblk_line_retry(pblk, new);
		if (!new)
			goto out;

		goto retry_setup;
	}

	if (!pblk_line_init_bb(pblk, new, 1)) {
		new = pblk_line_retry(pblk, new);
		if (!new)
			goto out;

		goto retry_setup;
	}

	pblk_rl_free_lines_dec(&pblk->rl, new, true);

	/* Allocate next line for preparation */
	spin_lock(&l_mg->free_lock);
	l_mg->data_next = pblk_line_get(pblk);
	if (!l_mg->data_next) {
		/* If we cannot get a new line, we need to stop the pipeline.
		 * Only allow as many writes in as we can store safely and then
		 * fail gracefully
		 */
		pblk_stop_writes(pblk, new);
		l_mg->data_next = NULL;
	} else {
		l_mg->data_next->seq_nr = l_mg->d_seq_nr++;
		l_mg->data_next->type = PBLK_LINETYPE_DATA;
	}
	spin_unlock(&l_mg->free_lock);

out:
	return new;
}