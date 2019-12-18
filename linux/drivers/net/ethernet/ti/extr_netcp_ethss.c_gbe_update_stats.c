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
struct gbe_priv {int num_et_stats; int /*<<< orphan*/ * hw_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  gbe_update_hw_stats_entry (struct gbe_priv*,int) ; 

__attribute__((used)) static void gbe_update_stats(struct gbe_priv *gbe_dev, uint64_t *data)
{
	int i;

	for (i = 0; i < gbe_dev->num_et_stats; i++) {
		gbe_update_hw_stats_entry(gbe_dev, i);

		if (data)
			data[i] = gbe_dev->hw_stats[i];
	}
}