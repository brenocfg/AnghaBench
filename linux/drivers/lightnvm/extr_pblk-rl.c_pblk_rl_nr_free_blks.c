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
struct pblk_rl {int /*<<< orphan*/  free_blocks; } ;

/* Variables and functions */
 unsigned long atomic_read (int /*<<< orphan*/ *) ; 

unsigned long pblk_rl_nr_free_blks(struct pblk_rl *rl)
{
	return atomic_read(&rl->free_blocks);
}