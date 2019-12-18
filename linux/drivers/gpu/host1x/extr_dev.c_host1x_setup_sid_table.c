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
struct host1x_sid_entry {scalar_t__ base; int /*<<< orphan*/  limit; int /*<<< orphan*/  offset; } ;
struct host1x_info {unsigned int num_sid_entries; struct host1x_sid_entry* sid_table; } ;
struct host1x {struct host1x_info* info; } ;

/* Variables and functions */
 int /*<<< orphan*/  host1x_hypervisor_writel (struct host1x*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void host1x_setup_sid_table(struct host1x *host)
{
	const struct host1x_info *info = host->info;
	unsigned int i;

	for (i = 0; i < info->num_sid_entries; i++) {
		const struct host1x_sid_entry *entry = &info->sid_table[i];

		host1x_hypervisor_writel(host, entry->offset, entry->base);
		host1x_hypervisor_writel(host, entry->limit, entry->base + 4);
	}
}