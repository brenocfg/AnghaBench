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
struct pblk_line_mgmt {int /*<<< orphan*/  free_lock; int /*<<< orphan*/  free_list; struct pblk_line* data_line; } ;
struct pblk_line {int /*<<< orphan*/  list; } ;
struct pblk {int /*<<< orphan*/  rl; struct pblk_line_mgmt l_mg; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int pblk_line_alloc_bitmaps (struct pblk*,struct pblk_line*) ; 
 int /*<<< orphan*/  pblk_line_init_bb (struct pblk*,struct pblk_line*,int /*<<< orphan*/ ) ; 
 int pblk_line_prepare (struct pblk*,struct pblk_line*) ; 
 int /*<<< orphan*/  pblk_rl_free_lines_dec (int /*<<< orphan*/ *,struct pblk_line*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int pblk_line_recov_alloc(struct pblk *pblk, struct pblk_line *line)
{
	struct pblk_line_mgmt *l_mg = &pblk->l_mg;
	int ret;

	spin_lock(&l_mg->free_lock);
	l_mg->data_line = line;
	list_del(&line->list);

	ret = pblk_line_prepare(pblk, line);
	if (ret) {
		list_add(&line->list, &l_mg->free_list);
		spin_unlock(&l_mg->free_lock);
		return ret;
	}
	spin_unlock(&l_mg->free_lock);

	ret = pblk_line_alloc_bitmaps(pblk, line);
	if (ret)
		goto fail;

	if (!pblk_line_init_bb(pblk, line, 0)) {
		ret = -EINTR;
		goto fail;
	}

	pblk_rl_free_lines_dec(&pblk->rl, line, true);
	return 0;

fail:
	spin_lock(&l_mg->free_lock);
	list_add(&line->list, &l_mg->free_list);
	spin_unlock(&l_mg->free_lock);

	return ret;
}