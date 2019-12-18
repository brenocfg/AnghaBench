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
struct ocelot {int shared_queue_sz; int* base_mac; int /*<<< orphan*/  num_stats; int /*<<< orphan*/  stats_layout; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_random_addr (int*) ; 
 int /*<<< orphan*/  ocelot_pll5_init (struct ocelot*) ; 
 int /*<<< orphan*/  ocelot_regfields ; 
 int ocelot_regfields_init (struct ocelot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocelot_regmap ; 
 int /*<<< orphan*/  ocelot_stats_layout ; 

int ocelot_chip_init(struct ocelot *ocelot)
{
	int ret;

	ocelot->map = ocelot_regmap;
	ocelot->stats_layout = ocelot_stats_layout;
	ocelot->num_stats = ARRAY_SIZE(ocelot_stats_layout);
	ocelot->shared_queue_sz = 224 * 1024;

	ret = ocelot_regfields_init(ocelot, ocelot_regfields);
	if (ret)
		return ret;

	ocelot_pll5_init(ocelot);

	eth_random_addr(ocelot->base_mac);
	ocelot->base_mac[5] &= 0xf0;

	return 0;
}