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
struct pblk {int /*<<< orphan*/  rwb; } ;

/* Variables and functions */
 int /*<<< orphan*/  pblk_rb_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pblk_rb_sync_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pblk_write_kick (struct pblk*) ; 
 int /*<<< orphan*/  schedule () ; 

__attribute__((used)) static void pblk_flush_writer(struct pblk *pblk)
{
	pblk_rb_flush(&pblk->rwb);
	do {
		if (!pblk_rb_sync_count(&pblk->rwb))
			break;

		pblk_write_kick(pblk);
		schedule();
	} while (1);
}