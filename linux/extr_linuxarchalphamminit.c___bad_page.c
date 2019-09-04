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

/* Variables and functions */
 scalar_t__ EMPTY_PGE ; 
 int /*<<< orphan*/  PAGE_SHARED ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mk_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkdirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (scalar_t__) ; 

pte_t
__bad_page(void)
{
	memset((void *) EMPTY_PGE, 0, PAGE_SIZE);
	return pte_mkdirty(mk_pte(virt_to_page(EMPTY_PGE), PAGE_SHARED));
}