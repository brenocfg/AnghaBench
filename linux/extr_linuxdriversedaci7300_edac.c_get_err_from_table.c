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
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static const char *get_err_from_table(const char *table[], int size, int pos)
{
	if (unlikely(pos >= size))
		return "Reserved";

	if (unlikely(!table[pos]))
		return "Reserved";

	return table[pos];
}