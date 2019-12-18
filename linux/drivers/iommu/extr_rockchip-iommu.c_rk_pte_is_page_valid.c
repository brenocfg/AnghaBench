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
typedef  int u32 ;

/* Variables and functions */
 int RK_PTE_PAGE_VALID ; 

__attribute__((used)) static inline bool rk_pte_is_page_valid(u32 pte)
{
	return pte & RK_PTE_PAGE_VALID;
}