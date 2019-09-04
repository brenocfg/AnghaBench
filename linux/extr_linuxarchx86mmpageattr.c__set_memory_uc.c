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

/* Variables and functions */
 int /*<<< orphan*/  _PAGE_CACHE_MODE_UC_MINUS ; 
 int /*<<< orphan*/  cachemode2pgprot (int /*<<< orphan*/ ) ; 
 int change_page_attr_set (unsigned long*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int _set_memory_uc(unsigned long addr, int numpages)
{
	/*
	 * for now UC MINUS. see comments in ioremap_nocache()
	 * If you really need strong UC use ioremap_uc(), but note
	 * that you cannot override IO areas with set_memory_*() as
	 * these helpers cannot work with IO memory.
	 */
	return change_page_attr_set(&addr, numpages,
				    cachemode2pgprot(_PAGE_CACHE_MODE_UC_MINUS),
				    0);
}