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
 int /*<<< orphan*/  pblk_err (struct pblk*,char*) ; 
 int /*<<< orphan*/  pblk_rb_free (int /*<<< orphan*/ *) ; 
 scalar_t__ pblk_rb_tear_down_check (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pblk_rwb_free(struct pblk *pblk)
{
	if (pblk_rb_tear_down_check(&pblk->rwb))
		pblk_err(pblk, "write buffer error on tear down\n");

	pblk_rb_free(&pblk->rwb);
}