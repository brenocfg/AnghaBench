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
struct pblk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pblk*) ; 
 int /*<<< orphan*/  pblk_core_free (struct pblk*) ; 
 int /*<<< orphan*/  pblk_l2p_free (struct pblk*) ; 
 int /*<<< orphan*/  pblk_lines_free (struct pblk*) ; 
 int /*<<< orphan*/  pblk_rwb_free (struct pblk*) ; 

__attribute__((used)) static void pblk_free(struct pblk *pblk)
{
	pblk_lines_free(pblk);
	pblk_l2p_free(pblk);
	pblk_rwb_free(pblk);
	pblk_core_free(pblk);

	kfree(pblk);
}