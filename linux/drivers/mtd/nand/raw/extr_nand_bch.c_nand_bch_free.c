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
struct nand_bch_control {struct nand_bch_control* eccmask; struct nand_bch_control* errloc; int /*<<< orphan*/  bch; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_bch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nand_bch_control*) ; 

void nand_bch_free(struct nand_bch_control *nbc)
{
	if (nbc) {
		free_bch(nbc->bch);
		kfree(nbc->errloc);
		kfree(nbc->eccmask);
		kfree(nbc);
	}
}