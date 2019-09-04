#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  format; } ;
struct TYPE_3__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int ETH_GSTRING_LEN ; 
#define  ETH_SS_STATS 128 
 int NUM_VPORT_REP_HW_COUNTERS ; 
 int NUM_VPORT_REP_SW_COUNTERS ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* sw_rep_stats_desc ; 
 TYPE_1__* vport_rep_stats_desc ; 

__attribute__((used)) static void mlx5e_rep_get_strings(struct net_device *dev,
				  u32 stringset, uint8_t *data)
{
	int i, j;

	switch (stringset) {
	case ETH_SS_STATS:
		for (i = 0; i < NUM_VPORT_REP_SW_COUNTERS; i++)
			strcpy(data + (i * ETH_GSTRING_LEN),
			       sw_rep_stats_desc[i].format);
		for (j = 0; j < NUM_VPORT_REP_HW_COUNTERS; j++, i++)
			strcpy(data + (i * ETH_GSTRING_LEN),
			       vport_rep_stats_desc[j].format);
		break;
	}
}