#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pblk_line_meta {int blk_per_line; } ;
struct pblk_line {TYPE_1__* chks; } ;
struct pblk {struct pblk_line_meta lm; } ;
struct TYPE_2__ {int state; } ;

/* Variables and functions */
 int NVM_CHK_ST_OPEN ; 

__attribute__((used)) static bool pblk_line_is_open(struct pblk *pblk, struct pblk_line *line)
{
	struct pblk_line_meta *lm = &pblk->lm;
	int i;

	for (i = 0; i < lm->blk_per_line; i++)
		if (line->chks[i].state & NVM_CHK_ST_OPEN)
			return true;

	return false;
}