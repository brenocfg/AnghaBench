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
struct pblk_w_err_gc {int dummy; } ;
struct pblk_line_meta {int blk_bitmap_len; int /*<<< orphan*/  blk_per_line; } ;
struct pblk_line {void* blk_bitmap; void* erase_bitmap; void* chks; void* w_err_gc; } ;
struct pblk {struct pblk_line_meta lm; } ;
struct nvm_chk_meta {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc_array (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pblk_alloc_line_meta(struct pblk *pblk, struct pblk_line *line)
{
	struct pblk_line_meta *lm = &pblk->lm;

	line->blk_bitmap = kzalloc(lm->blk_bitmap_len, GFP_KERNEL);
	if (!line->blk_bitmap)
		return -ENOMEM;

	line->erase_bitmap = kzalloc(lm->blk_bitmap_len, GFP_KERNEL);
	if (!line->erase_bitmap)
		goto free_blk_bitmap;


	line->chks = kmalloc_array(lm->blk_per_line,
				   sizeof(struct nvm_chk_meta), GFP_KERNEL);
	if (!line->chks)
		goto free_erase_bitmap;

	line->w_err_gc = kzalloc(sizeof(struct pblk_w_err_gc), GFP_KERNEL);
	if (!line->w_err_gc)
		goto free_chks;

	return 0;

free_chks:
	kfree(line->chks);
free_erase_bitmap:
	kfree(line->erase_bitmap);
free_blk_bitmap:
	kfree(line->blk_bitmap);
	return -ENOMEM;
}