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
 int /*<<< orphan*/  __pa_symbol (unsigned long*) ; 
 int /*<<< orphan*/  free_init_pages (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_init_pages_eva_malta(void *begin, void *end)
{
	free_init_pages("unused kernel", __pa_symbol((unsigned long *)begin),
			__pa_symbol((unsigned long *)end));
}