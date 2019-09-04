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
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  pgd_offset_k (unsigned long) ; 
 int /*<<< orphan*/ * pmd_off (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static inline pmd_t *pmd_off_k(unsigned long virt)
{
	return pmd_off(pgd_offset_k(virt), virt);
}