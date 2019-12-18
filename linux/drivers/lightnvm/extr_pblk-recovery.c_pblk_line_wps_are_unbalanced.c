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
typedef  scalar_t__ u64 ;
struct pblk_line_meta {int blk_per_line; } ;
struct pblk_line {int /*<<< orphan*/  blk_bitmap; } ;
struct pblk {scalar_t__ max_write_pgs; struct pblk_line_meta lm; } ;
struct nvm_chk_meta {scalar_t__ wp; } ;

/* Variables and functions */
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int find_next_zero_bit (int /*<<< orphan*/ ,int,int) ; 
 struct nvm_chk_meta* pblk_get_stripe_chunk (struct pblk*,struct pblk_line*,int) ; 

__attribute__((used)) static int pblk_line_wps_are_unbalanced(struct pblk *pblk,
				      struct pblk_line *line)
{
	struct pblk_line_meta *lm = &pblk->lm;
	int blk_in_line = lm->blk_per_line;
	struct nvm_chk_meta *chunk;
	u64 max_wp, min_wp;
	int i;

	i = find_first_zero_bit(line->blk_bitmap, blk_in_line);

	/* If there is one or zero good chunks in the line,
	 * the write pointers can't be unbalanced.
	 */
	if (i >= (blk_in_line - 1))
		return 0;

	chunk = pblk_get_stripe_chunk(pblk, line, i);
	max_wp = chunk->wp;
	if (max_wp > pblk->max_write_pgs)
		min_wp = max_wp - pblk->max_write_pgs;
	else
		min_wp = 0;

	i = find_next_zero_bit(line->blk_bitmap, blk_in_line, i + 1);
	while (i < blk_in_line) {
		chunk = pblk_get_stripe_chunk(pblk, line, i);
		if (chunk->wp > max_wp || chunk->wp < min_wp)
			return 1;

		i = find_next_zero_bit(line->blk_bitmap, blk_in_line, i + 1);
	}

	return 0;
}