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
 int /*<<< orphan*/  fast_clear_page (void*) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  slow_zero_page (void*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void mmx_clear_page(void *page)
{
	if (unlikely(in_interrupt()))
		slow_zero_page(page);
	else
		fast_clear_page(page);
}