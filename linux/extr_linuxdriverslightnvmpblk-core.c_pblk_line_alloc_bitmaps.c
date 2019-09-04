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
struct pblk_line_meta {int /*<<< orphan*/  sec_bitmap_len; } ;
struct pblk_line {int /*<<< orphan*/ * map_bitmap; int /*<<< orphan*/  invalid_bitmap; } ;
struct pblk {struct pblk_line_meta lm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pblk_line_alloc_bitmaps(struct pblk *pblk, struct pblk_line *line)
{
	struct pblk_line_meta *lm = &pblk->lm;

	line->map_bitmap = kzalloc(lm->sec_bitmap_len, GFP_KERNEL);
	if (!line->map_bitmap)
		return -ENOMEM;

	/* will be initialized using bb info from map_bitmap */
	line->invalid_bitmap = kmalloc(lm->sec_bitmap_len, GFP_KERNEL);
	if (!line->invalid_bitmap) {
		kfree(line->map_bitmap);
		line->map_bitmap = NULL;
		return -ENOMEM;
	}

	return 0;
}