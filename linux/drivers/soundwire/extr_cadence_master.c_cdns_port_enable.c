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
struct sdw_enable_ch {int ch_mask; int enable; int /*<<< orphan*/  port_num; } ;
struct sdw_cdns {int dummy; } ;
struct sdw_bus {int dummy; } ;

/* Variables and functions */
 int CDNS_DPN_B0_CH_EN (int /*<<< orphan*/ ) ; 
 int CDNS_DPN_B1_CH_EN (int /*<<< orphan*/ ) ; 
 struct sdw_cdns* bus_to_cdns (struct sdw_bus*) ; 
 int /*<<< orphan*/  cdns_writel (struct sdw_cdns*,int,int) ; 

__attribute__((used)) static int cdns_port_enable(struct sdw_bus *bus,
			    struct sdw_enable_ch *enable_ch, unsigned int bank)
{
	struct sdw_cdns *cdns = bus_to_cdns(bus);
	int dpn_chnen_off, ch_mask;

	if (bank)
		dpn_chnen_off = CDNS_DPN_B1_CH_EN(enable_ch->port_num);
	else
		dpn_chnen_off = CDNS_DPN_B0_CH_EN(enable_ch->port_num);

	ch_mask = enable_ch->ch_mask * enable_ch->enable;
	cdns_writel(cdns, dpn_chnen_off, ch_mask);

	return 0;
}