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
typedef  scalar_t__ u64 ;
struct pblk_line_meta {scalar_t__ sec_per_line; } ;
struct pblk {struct pblk_line_meta lm; } ;

/* Variables and functions */

__attribute__((used)) static inline int pblk_boundary_paddr_checks(struct pblk *pblk, u64 paddr)
{
	struct pblk_line_meta *lm = &pblk->lm;

	if (paddr > lm->sec_per_line)
		return 1;

	return 0;
}