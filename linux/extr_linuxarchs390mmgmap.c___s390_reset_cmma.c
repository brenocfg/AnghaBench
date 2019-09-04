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
struct mm_walk {int /*<<< orphan*/  mm; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  ptep_zap_unused (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int __s390_reset_cmma(pte_t *pte, unsigned long addr,
			     unsigned long next, struct mm_walk *walk)
{
	ptep_zap_unused(walk->mm, addr, pte, 1);
	return 0;
}