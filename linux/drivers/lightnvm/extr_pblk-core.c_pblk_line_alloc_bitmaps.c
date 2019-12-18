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
struct pblk_line_meta {int /*<<< orphan*/  sec_bitmap_len; } ;
struct pblk_line {int /*<<< orphan*/ * map_bitmap; void* invalid_bitmap; } ;
struct pblk {struct pblk_line_mgmt l_mg; struct pblk_line_meta lm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pblk_line_alloc_bitmaps(struct pblk *pblk, struct pblk_line *line)
{
	struct pblk_line_meta *lm = &pblk->lm;
	struct pblk_line_mgmt *l_mg = &pblk->l_mg;

	line->map_bitmap = mempool_alloc(l_mg->bitmap_pool, GFP_KERNEL);
	if (!line->map_bitmap)
		return -ENOMEM;

	memset(line->map_bitmap, 0, lm->sec_bitmap_len);

	/* will be initialized using bb info from map_bitmap */
	line->invalid_bitmap = mempool_alloc(l_mg->bitmap_pool, GFP_KERNEL);
	if (!line->invalid_bitmap) {
		mempool_free(line->map_bitmap, l_mg->bitmap_pool);
		line->map_bitmap = NULL;
		return -ENOMEM;
	}

	return 0;
}