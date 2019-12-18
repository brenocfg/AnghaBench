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
typedef  int /*<<< orphan*/  uint32_t ;
struct of_phandle_iterator {int cur_count; int /*<<< orphan*/  cur; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/ ) ; 

int of_phandle_iterator_args(struct of_phandle_iterator *it,
			     uint32_t *args,
			     int size)
{
	int i, count;

	count = it->cur_count;

	if (WARN_ON(size < count))
		count = size;

	for (i = 0; i < count; i++)
		args[i] = be32_to_cpup(it->cur++);

	return count;
}