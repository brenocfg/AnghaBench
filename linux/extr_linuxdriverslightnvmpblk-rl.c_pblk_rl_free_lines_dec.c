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
struct pblk_rl {int /*<<< orphan*/  free_user_blocks; int /*<<< orphan*/  free_blocks; } ;
struct pblk_line {int /*<<< orphan*/  blk_in_line; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pblk_rl_update_rates (struct pblk_rl*,int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int atomic_sub_return (int,int /*<<< orphan*/ *) ; 

void pblk_rl_free_lines_dec(struct pblk_rl *rl, struct pblk_line *line,
			    bool used)
{
	int blk_in_line = atomic_read(&line->blk_in_line);
	int free_blocks;

	atomic_sub(blk_in_line, &rl->free_blocks);

	if (used)
		free_blocks = atomic_sub_return(blk_in_line,
							&rl->free_user_blocks);
	else
		free_blocks = atomic_read(&rl->free_user_blocks);

	__pblk_rl_update_rates(rl, free_blocks);
}