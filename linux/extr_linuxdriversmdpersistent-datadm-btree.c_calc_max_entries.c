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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct node_header {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t calc_max_entries(size_t value_size, size_t block_size)
{
	uint32_t total, n;
	size_t elt_size = sizeof(uint64_t) + value_size; /* key + value */

	block_size -= sizeof(struct node_header);
	total = block_size / elt_size;
	n = total / 3;		/* rounds down */

	return 3 * n;
}