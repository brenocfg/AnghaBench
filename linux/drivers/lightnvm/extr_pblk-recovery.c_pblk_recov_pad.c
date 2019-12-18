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
struct pblk_line_mgmt {int /*<<< orphan*/  free_lock; struct pblk_line* data_line; } ;
struct pblk_line {int left_msecs; } ;
struct pblk {struct pblk_line_mgmt l_mg; } ;

/* Variables and functions */
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,int) ; 
 int /*<<< orphan*/  pblk_line_close_meta (struct pblk*,struct pblk_line*) ; 
 int pblk_recov_pad_line (struct pblk*,struct pblk_line*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int pblk_recov_pad(struct pblk *pblk)
{
	struct pblk_line *line;
	struct pblk_line_mgmt *l_mg = &pblk->l_mg;
	int left_msecs;
	int ret = 0;

	spin_lock(&l_mg->free_lock);
	line = l_mg->data_line;
	left_msecs = line->left_msecs;
	spin_unlock(&l_mg->free_lock);

	ret = pblk_recov_pad_line(pblk, line, left_msecs);
	if (ret) {
		pblk_err(pblk, "tear down padding failed (%d)\n", ret);
		return ret;
	}

	pblk_line_close_meta(pblk, line);
	return ret;
}