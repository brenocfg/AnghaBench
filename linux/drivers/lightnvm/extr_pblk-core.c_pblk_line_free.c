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
struct pblk_line_mgmt {int /*<<< orphan*/  bitmap_pool; } ;
struct pblk_line {int /*<<< orphan*/  invalid_bitmap; int /*<<< orphan*/  map_bitmap; struct pblk* pblk; } ;
struct pblk {struct pblk_line_mgmt l_mg; } ;

/* Variables and functions */
 int /*<<< orphan*/  mempool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_line_reinit (struct pblk_line*) ; 

void pblk_line_free(struct pblk_line *line)
{
	struct pblk *pblk = line->pblk;
	struct pblk_line_mgmt *l_mg = &pblk->l_mg;

	mempool_free(line->map_bitmap, l_mg->bitmap_pool);
	mempool_free(line->invalid_bitmap, l_mg->bitmap_pool);

	pblk_line_reinit(line);
}