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
struct orc_entry {int dummy; } ;

/* Variables and functions */
 int* cur_orc_ip_table ; 
 struct orc_entry* cur_orc_table ; 

__attribute__((used)) static void orc_sort_swap(void *_a, void *_b, int size)
{
	struct orc_entry *orc_a, *orc_b;
	struct orc_entry orc_tmp;
	int *a = _a, *b = _b, tmp;
	int delta = _b - _a;

	/* Swap the .orc_unwind_ip entries: */
	tmp = *a;
	*a = *b + delta;
	*b = tmp - delta;

	/* Swap the corresponding .orc_unwind entries: */
	orc_a = cur_orc_table + (a - cur_orc_ip_table);
	orc_b = cur_orc_table + (b - cur_orc_ip_table);
	orc_tmp = *orc_a;
	*orc_a = *orc_b;
	*orc_b = orc_tmp;
}