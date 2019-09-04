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
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int /*<<< orphan*/  __pgprot (int) ; 
 int /*<<< orphan*/  pfn_pte (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long pte_pfn (int /*<<< orphan*/ ) ; 
 int pte_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline pgprot_t pte_pgprot(pte_t pte)
{
	unsigned long pfn = pte_pfn(pte);

	return __pgprot(pte_val(pfn_pte(pfn, __pgprot(0))) ^ pte_val(pte));
}