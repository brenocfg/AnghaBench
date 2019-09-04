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
struct nfp_eth_table_port {int dummy; } ;
struct ethtool_link_ksettings {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FEC_BASER ; 
 int /*<<< orphan*/  FEC_NONE ; 
 int /*<<< orphan*/  FEC_RS ; 
 unsigned int NFP_FEC_BASER ; 
 unsigned int NFP_FEC_REED_SOLOMON ; 
 int /*<<< orphan*/  advertising ; 
 int /*<<< orphan*/  ethtool_link_ksettings_add_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_eth_can_support_fec (struct nfp_eth_table_port*) ; 
 unsigned int nfp_eth_supported_fec_modes (struct nfp_eth_table_port*) ; 
 int /*<<< orphan*/  supported ; 

__attribute__((used)) static void
nfp_net_set_fec_link_mode(struct nfp_eth_table_port *eth_port,
			  struct ethtool_link_ksettings *c)
{
	unsigned int modes;

	ethtool_link_ksettings_add_link_mode(c, supported, FEC_NONE);
	if (!nfp_eth_can_support_fec(eth_port)) {
		ethtool_link_ksettings_add_link_mode(c, advertising, FEC_NONE);
		return;
	}

	modes = nfp_eth_supported_fec_modes(eth_port);
	if (modes & NFP_FEC_BASER) {
		ethtool_link_ksettings_add_link_mode(c, supported, FEC_BASER);
		ethtool_link_ksettings_add_link_mode(c, advertising, FEC_BASER);
	}

	if (modes & NFP_FEC_REED_SOLOMON) {
		ethtool_link_ksettings_add_link_mode(c, supported, FEC_RS);
		ethtool_link_ksettings_add_link_mode(c, advertising, FEC_RS);
	}
}