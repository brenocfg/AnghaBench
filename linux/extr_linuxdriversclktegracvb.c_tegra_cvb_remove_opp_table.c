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
struct device {int dummy; } ;
struct cvb_table_freq_entry {unsigned long freq; } ;
struct cvb_table {struct cvb_table_freq_entry* entries; } ;

/* Variables and functions */
 unsigned int MAX_DVFS_FREQS ; 
 int /*<<< orphan*/  dev_pm_opp_remove (struct device*,unsigned long) ; 

void tegra_cvb_remove_opp_table(struct device *dev,
				const struct cvb_table *table,
				unsigned long max_freq)
{
	unsigned int i;

	for (i = 0; i < MAX_DVFS_FREQS; i++) {
		const struct cvb_table_freq_entry *entry = &table->entries[i];

		if (!entry->freq || (entry->freq > max_freq))
			break;

		dev_pm_opp_remove(dev, entry->freq);
	}
}