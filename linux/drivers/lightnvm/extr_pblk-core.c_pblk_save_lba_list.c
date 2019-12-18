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
struct pblk_w_err_gc {int /*<<< orphan*/  lba_list; } ;
struct pblk_line_meta {unsigned int* emeta_len; } ;
struct pblk_line {struct pblk_emeta* emeta; struct pblk_w_err_gc* w_err_gc; } ;
struct pblk_emeta {int /*<<< orphan*/  buf; } ;
struct pblk {struct pblk_line_meta lm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  emeta_to_lbas (struct pblk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void pblk_save_lba_list(struct pblk *pblk, struct pblk_line *line)
{
	struct pblk_line_meta *lm = &pblk->lm;
	unsigned int lba_list_size = lm->emeta_len[2];
	struct pblk_w_err_gc *w_err_gc = line->w_err_gc;
	struct pblk_emeta *emeta = line->emeta;

	w_err_gc->lba_list = kvmalloc(lba_list_size, GFP_KERNEL);
	memcpy(w_err_gc->lba_list, emeta_to_lbas(pblk, emeta->buf),
				lba_list_size);
}