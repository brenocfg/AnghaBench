#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sja1105_static_config {TYPE_1__* tables; } ;
typedef  enum sja1105_blk_idx { ____Placeholder_sja1105_blk_idx } sja1105_blk_idx ;
struct TYPE_2__ {scalar_t__ entry_count; int /*<<< orphan*/  entries; } ;

/* Variables and functions */
 int BLK_IDX_MAX ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void sja1105_static_config_free(struct sja1105_static_config *config)
{
	enum sja1105_blk_idx i;

	for (i = 0; i < BLK_IDX_MAX; i++) {
		if (config->tables[i].entry_count) {
			kfree(config->tables[i].entries);
			config->tables[i].entry_count = 0;
		}
	}
}