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
struct ll_disk {int dummy; } ;
typedef  unsigned long long dm_block_t ;

/* Variables and functions */

__attribute__((used)) static dm_block_t disk_ll_max_entries(struct ll_disk *ll)
{
	return -1ULL;
}