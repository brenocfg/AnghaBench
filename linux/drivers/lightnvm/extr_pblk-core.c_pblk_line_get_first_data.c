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
struct pblk_line_mgmt {int /*<<< orphan*/  free_lock; TYPE_1__* data_next; int /*<<< orphan*/  d_seq_nr; struct pblk_line* data_line; } ;
struct pblk_line {void* type; scalar_t__ seq_nr; } ;
struct pblk {int /*<<< orphan*/  rl; int /*<<< orphan*/  lm; struct pblk_line_mgmt l_mg; } ;
struct TYPE_2__ {void* type; scalar_t__ seq_nr; } ;

/* Variables and functions */
 void* PBLK_LINETYPE_DATA ; 
 scalar_t__ pblk_line_alloc_bitmaps (struct pblk*,struct pblk_line*) ; 
 scalar_t__ pblk_line_erase (struct pblk*,struct pblk_line*) ; 
 void* pblk_line_get (struct pblk*) ; 
 int /*<<< orphan*/  pblk_line_init_bb (struct pblk*,struct pblk_line*,int) ; 
 int /*<<< orphan*/  pblk_line_init_metadata (struct pblk*,struct pblk_line*,int /*<<< orphan*/ *) ; 
 struct pblk_line* pblk_line_retry (struct pblk*,struct pblk_line*) ; 
 int /*<<< orphan*/  pblk_line_setup_metadata (struct pblk_line*,struct pblk_line_mgmt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pblk_rl_free_lines_dec (int /*<<< orphan*/ *,struct pblk_line*,int) ; 
 int /*<<< orphan*/  pblk_set_space_limit (struct pblk*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct pblk_line *pblk_line_get_first_data(struct pblk *pblk)
{
	struct pblk_line_mgmt *l_mg = &pblk->l_mg;
	struct pblk_line *line;

	spin_lock(&l_mg->free_lock);
	line = pblk_line_get(pblk);
	if (!line) {
		spin_unlock(&l_mg->free_lock);
		return NULL;
	}

	line->seq_nr = l_mg->d_seq_nr++;
	line->type = PBLK_LINETYPE_DATA;
	l_mg->data_line = line;

	pblk_line_setup_metadata(line, l_mg, &pblk->lm);

	/* Allocate next line for preparation */
	l_mg->data_next = pblk_line_get(pblk);
	if (!l_mg->data_next) {
		/* If we cannot get a new line, we need to stop the pipeline.
		 * Only allow as many writes in as we can store safely and then
		 * fail gracefully
		 */
		pblk_set_space_limit(pblk);

		l_mg->data_next = NULL;
	} else {
		l_mg->data_next->seq_nr = l_mg->d_seq_nr++;
		l_mg->data_next->type = PBLK_LINETYPE_DATA;
	}
	spin_unlock(&l_mg->free_lock);

	if (pblk_line_alloc_bitmaps(pblk, line))
		return NULL;

	if (pblk_line_erase(pblk, line)) {
		line = pblk_line_retry(pblk, line);
		if (!line)
			return NULL;
	}

retry_setup:
	if (!pblk_line_init_metadata(pblk, line, NULL)) {
		line = pblk_line_retry(pblk, line);
		if (!line)
			return NULL;

		goto retry_setup;
	}

	if (!pblk_line_init_bb(pblk, line, 1)) {
		line = pblk_line_retry(pblk, line);
		if (!line)
			return NULL;

		goto retry_setup;
	}

	pblk_rl_free_lines_dec(&pblk->rl, line, true);

	return line;
}