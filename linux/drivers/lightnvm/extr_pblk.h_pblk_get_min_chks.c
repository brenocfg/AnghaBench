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
struct pblk_line_meta {unsigned int blk_per_line; } ;
struct pblk {int /*<<< orphan*/  op; struct pblk_line_meta lm; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int pblk_get_min_chks(struct pblk *pblk)
{
	struct pblk_line_meta *lm = &pblk->lm;
	/* In a worst-case scenario every line will have OP invalid sectors.
	 * We will then need a minimum of 1/OP lines to free up a single line
	 */

	return DIV_ROUND_UP(100, pblk->op) * lm->blk_per_line;
}