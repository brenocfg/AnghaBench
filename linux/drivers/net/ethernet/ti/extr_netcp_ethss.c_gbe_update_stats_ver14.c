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
typedef  int u32 ;
struct gbe_priv {int num_et_stats; int /*<<< orphan*/ * hw_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  GBE_STATSA_MODULE ; 
 int /*<<< orphan*/  GBE_STATSC_MODULE ; 
 int /*<<< orphan*/  gbe_stats_mod_visible_ver14 (struct gbe_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gbe_update_hw_stats_entry (struct gbe_priv*,int) ; 

__attribute__((used)) static void gbe_update_stats_ver14(struct gbe_priv *gbe_dev, uint64_t *data)
{
	u32 half_num_et_stats = (gbe_dev->num_et_stats / 2);
	int et_entry, j, pair;

	for (pair = 0; pair < 2; pair++) {
		gbe_stats_mod_visible_ver14(gbe_dev, (pair ?
						      GBE_STATSC_MODULE :
						      GBE_STATSA_MODULE));

		for (j = 0; j < half_num_et_stats; j++) {
			et_entry = pair * half_num_et_stats + j;
			gbe_update_hw_stats_entry(gbe_dev, et_entry);

			if (data)
				data[et_entry] = gbe_dev->hw_stats[et_entry];
		}
	}
}