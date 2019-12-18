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
struct pblk_rl {int /*<<< orphan*/  werr_lines; } ;
struct pblk_gc {scalar_t__ gc_active; } ;

/* Variables and functions */
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 unsigned int pblk_rl_high_thrs (struct pblk_rl*) ; 
 unsigned int pblk_rl_nr_free_blks (struct pblk_rl*) ; 

__attribute__((used)) static bool pblk_gc_should_run(struct pblk_gc *gc, struct pblk_rl *rl)
{
	unsigned int nr_blocks_free, nr_blocks_need;
	unsigned int werr_lines = atomic_read(&rl->werr_lines);

	nr_blocks_need = pblk_rl_high_thrs(rl);
	nr_blocks_free = pblk_rl_nr_free_blks(rl);

	/* This is not critical, no need to take lock here */
	return ((werr_lines > 0) ||
		((gc->gc_active) && (nr_blocks_need > nr_blocks_free)));
}