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
struct ksz_desc_info {scalar_t__ next; scalar_t__ last; int /*<<< orphan*/  alloc; int /*<<< orphan*/  avail; int /*<<< orphan*/  ring; int /*<<< orphan*/  cur; } ;

/* Variables and functions */

__attribute__((used)) static void hw_reset_pkts(struct ksz_desc_info *info)
{
	info->cur = info->ring;
	info->avail = info->alloc;
	info->last = info->next = 0;
}