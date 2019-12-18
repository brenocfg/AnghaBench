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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5e_priv {int dummy; } ;
struct TYPE_2__ {char* format; } ;

/* Variables and functions */
 int ETH_GSTRING_LEN ; 
 int NUM_PPORT_PER_PRIO_TRAFFIC_COUNTERS ; 
 int NUM_PPORT_PRIO ; 
 TYPE_1__* pport_per_prio_traffic_stats_desc ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int mlx5e_grp_per_prio_traffic_fill_strings(struct mlx5e_priv *priv,
						   u8 *data,
						   int idx)
{
	int i, prio;

	for (prio = 0; prio < NUM_PPORT_PRIO; prio++) {
		for (i = 0; i < NUM_PPORT_PER_PRIO_TRAFFIC_COUNTERS; i++)
			sprintf(data + (idx++) * ETH_GSTRING_LEN,
				pport_per_prio_traffic_stats_desc[i].format, prio);
	}

	return idx;
}