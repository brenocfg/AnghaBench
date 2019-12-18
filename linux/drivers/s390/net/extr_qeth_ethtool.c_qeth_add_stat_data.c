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
typedef  int /*<<< orphan*/  u64 ;
struct qeth_stats {int offset; } ;

/* Variables and functions */

__attribute__((used)) static void qeth_add_stat_data(u64 **dst, void *src,
			       const struct qeth_stats stats[],
			       unsigned int size)
{
	unsigned int i;
	char *stat;

	for (i = 0; i < size; i++) {
		stat = (char *)src + stats[i].offset;
		**dst = *(u64 *)stat;
		(*dst)++;
	}
}