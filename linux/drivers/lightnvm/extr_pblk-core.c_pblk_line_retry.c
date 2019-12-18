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
struct pblk_line {int /*<<< orphan*/  meta_line; int /*<<< orphan*/  emeta; int /*<<< orphan*/  smeta; int /*<<< orphan*/  invalid_bitmap; int /*<<< orphan*/  map_bitmap; } ;
struct pblk {int /*<<< orphan*/  rl; struct pblk_line_mgmt l_mg; } ;

/* Variables and functions */
 scalar_t__ pblk_line_erase (struct pblk*,struct pblk_line*) ; 
 struct pblk_line* pblk_line_get (struct pblk*) ; 
 int /*<<< orphan*/  pblk_line_reinit (struct pblk_line*) ; 
 int /*<<< orphan*/  pblk_rl_free_lines_dec (int /*<<< orphan*/ *,struct pblk_line*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct pblk_line *pblk_line_retry(struct pblk *pblk,
					 struct pblk_line *line)
{
	struct pblk_line_mgmt *l_mg = &pblk->l_mg;
	struct pblk_line *retry_line;

retry:
	spin_lock(&l_mg->free_lock);
	retry_line = pblk_line_get(pblk);
	if (!retry_line) {
		l_mg->data_line = NULL;
		spin_unlock(&l_mg->free_lock);
		return NULL;
	}

	retry_line->map_bitmap = line->map_bitmap;
	retry_line->invalid_bitmap = line->invalid_bitmap;
	retry_line->smeta = line->smeta;
	retry_line->emeta = line->emeta;
	retry_line->meta_line = line->meta_line;

	pblk_line_reinit(line);

	l_mg->data_line = retry_line;
	spin_unlock(&l_mg->free_lock);

	pblk_rl_free_lines_dec(&pblk->rl, line, false);

	if (pblk_line_erase(pblk, retry_line))
		goto retry;

	return retry_line;
}