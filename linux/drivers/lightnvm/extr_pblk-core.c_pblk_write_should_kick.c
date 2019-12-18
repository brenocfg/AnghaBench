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
struct pblk {unsigned int min_write_pgs_data; int /*<<< orphan*/  rwb; } ;

/* Variables and functions */
 unsigned int pblk_rb_read_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pblk_write_kick (struct pblk*) ; 

void pblk_write_should_kick(struct pblk *pblk)
{
	unsigned int secs_avail = pblk_rb_read_count(&pblk->rwb);

	if (secs_avail >= pblk->min_write_pgs_data)
		pblk_write_kick(pblk);
}