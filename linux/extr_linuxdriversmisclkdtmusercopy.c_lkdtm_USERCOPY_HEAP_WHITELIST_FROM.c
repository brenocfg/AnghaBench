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
 int /*<<< orphan*/  do_usercopy_heap_whitelist (int) ; 

void lkdtm_USERCOPY_HEAP_WHITELIST_FROM(void)
{
	do_usercopy_heap_whitelist(false);
}