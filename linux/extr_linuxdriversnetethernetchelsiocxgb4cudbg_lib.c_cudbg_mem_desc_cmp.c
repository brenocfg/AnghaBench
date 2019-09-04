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
struct cudbg_mem_desc {int base; } ;

/* Variables and functions */

__attribute__((used)) static int cudbg_mem_desc_cmp(const void *a, const void *b)
{
	return ((const struct cudbg_mem_desc *)a)->base -
	       ((const struct cudbg_mem_desc *)b)->base;
}