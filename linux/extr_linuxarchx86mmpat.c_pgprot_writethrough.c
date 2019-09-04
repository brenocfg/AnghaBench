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
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int /*<<< orphan*/  _PAGE_CACHE_MODE_WT ; 
 int /*<<< orphan*/  __pgprot (int) ; 
 int cachemode2protval (int /*<<< orphan*/ ) ; 
 int pgprot_val (int /*<<< orphan*/ ) ; 

pgprot_t pgprot_writethrough(pgprot_t prot)
{
	return __pgprot(pgprot_val(prot) |
				cachemode2protval(_PAGE_CACHE_MODE_WT));
}