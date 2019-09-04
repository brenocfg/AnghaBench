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
 int _PAGE_NO_CACHE ; 
 int _PAGE_PRESENT ; 
 int _PAGE_PRIVILEGED ; 
 int _PAGE_SPECIAL ; 
 int _PAGE_USER ; 
 int pte_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int pte_looks_normal(pte_t pte)
{

#if defined(CONFIG_PPC_BOOK3S_64)
	if ((pte_val(pte) & (_PAGE_PRESENT | _PAGE_SPECIAL)) == _PAGE_PRESENT) {
		if (pte_ci(pte))
			return 0;
		if (pte_user(pte))
			return 1;
	}
	return 0;
#else
	return (pte_val(pte) &
		(_PAGE_PRESENT | _PAGE_SPECIAL | _PAGE_NO_CACHE | _PAGE_USER |
		 _PAGE_PRIVILEGED)) ==
		(_PAGE_PRESENT | _PAGE_USER);
#endif
}