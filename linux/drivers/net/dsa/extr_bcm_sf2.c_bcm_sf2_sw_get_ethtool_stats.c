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
struct dsa_switch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_SS_STATS ; 
 int /*<<< orphan*/  b53_get_ethtool_stats (struct dsa_switch*,int,int /*<<< orphan*/ *) ; 
 int b53_get_sset_count (struct dsa_switch*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_sf2_cfp_get_ethtool_stats (struct dsa_switch*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcm_sf2_sw_get_ethtool_stats(struct dsa_switch *ds, int port,
					 uint64_t *data)
{
	int cnt = b53_get_sset_count(ds, port, ETH_SS_STATS);

	b53_get_ethtool_stats(ds, port, data);
	bcm_sf2_cfp_get_ethtool_stats(ds, port, data + cnt);
}