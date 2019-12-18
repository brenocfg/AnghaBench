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
typedef  int u64 ;
typedef  int u32 ;
struct ocelot {int num_phys_ports; int num_stats; int* stats; int /*<<< orphan*/  stats_lock; TYPE_1__* stats_layout; } ;
struct TYPE_2__ {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_COUNT_RX_OCTETS ; 
 int /*<<< orphan*/  SYS_STAT_CFG ; 
 int /*<<< orphan*/  SYS_STAT_CFG_STAT_VIEW (int) ; 
 int U32_MAX ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ocelot_read_rix (struct ocelot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocelot_write (struct ocelot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocelot_update_stats(struct ocelot *ocelot)
{
	int i, j;

	mutex_lock(&ocelot->stats_lock);

	for (i = 0; i < ocelot->num_phys_ports; i++) {
		/* Configure the port to read the stats from */
		ocelot_write(ocelot, SYS_STAT_CFG_STAT_VIEW(i), SYS_STAT_CFG);

		for (j = 0; j < ocelot->num_stats; j++) {
			u32 val;
			unsigned int idx = i * ocelot->num_stats + j;

			val = ocelot_read_rix(ocelot, SYS_COUNT_RX_OCTETS,
					      ocelot->stats_layout[j].offset);

			if (val < (ocelot->stats[idx] & U32_MAX))
				ocelot->stats[idx] += (u64)1 << 32;

			ocelot->stats[idx] = (ocelot->stats[idx] &
					      ~(u64)U32_MAX) + val;
		}
	}

	mutex_unlock(&ocelot->stats_lock);
}