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

__attribute__((used)) static inline const char *fc_exch_name_lookup(unsigned int op, char **table,
					      unsigned int max_index)
{
	const char *name = NULL;

	if (op < max_index)
		name = table[op];
	if (!name)
		name = "unknown";
	return name;
}