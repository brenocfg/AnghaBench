#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct mac_hw_stats {int dummy; } ;
struct mac_driver {TYPE_1__* mac_cb; } ;
struct TYPE_5__ {int /*<<< orphan*/  offset; } ;
struct TYPE_4__ {struct mac_hw_stats hw_stats; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  DSAF_STATS_READ (struct mac_hw_stats*,int /*<<< orphan*/ ) ; 
 TYPE_2__* g_gmac_stats_string ; 

__attribute__((used)) static void hns_gmac_get_stats(void *mac_drv, u64 *data)
{
	u32 i;
	u64 *buf = data;
	struct mac_driver *drv = (struct mac_driver *)mac_drv;
	struct mac_hw_stats *hw_stats = NULL;

	hw_stats = &drv->mac_cb->hw_stats;

	for (i = 0; i < ARRAY_SIZE(g_gmac_stats_string); i++) {
		buf[i] = DSAF_STATS_READ(hw_stats,
			g_gmac_stats_string[i].offset);
	}
}