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
union eth_table_entry {int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  state; int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  u64 ;
struct nfp_nsp {int dummy; } ;
struct nfp_eth_table_port {int eth_index; unsigned int index; unsigned int nbi; unsigned int base; int lanes; int enabled; int tx_enabled; int rx_enabled; unsigned int speed; int interface; int media; int label_port; int label_subport; int override_changed; int aneg; unsigned int fec_modes_supported; int fec; int /*<<< orphan*/  mac_addr; } ;

/* Variables and functions */
 int FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NFP_FEC_AUTO ; 
 unsigned int NFP_FEC_BASER_BIT ; 
 int NFP_FEC_DISABLED ; 
 unsigned int NFP_FEC_REED_SOLOMON_BIT ; 
 unsigned int NSP_ETH_NBI_PORT_COUNT ; 
 int /*<<< orphan*/  NSP_ETH_PORT_FEC_SUPP_BASER ; 
 int /*<<< orphan*/  NSP_ETH_PORT_FEC_SUPP_RS ; 
 int /*<<< orphan*/  NSP_ETH_PORT_INDEX ; 
 int /*<<< orphan*/  NSP_ETH_PORT_LABEL ; 
 int /*<<< orphan*/  NSP_ETH_PORT_LANES ; 
 int /*<<< orphan*/  NSP_ETH_PORT_PHYLABEL ; 
 int /*<<< orphan*/  NSP_ETH_STATE_ANEG ; 
 int /*<<< orphan*/  NSP_ETH_STATE_ENABLED ; 
 int /*<<< orphan*/  NSP_ETH_STATE_FEC ; 
 int /*<<< orphan*/  NSP_ETH_STATE_INTERFACE ; 
 int /*<<< orphan*/  NSP_ETH_STATE_MEDIA ; 
 int /*<<< orphan*/  NSP_ETH_STATE_OVRD_CHNG ; 
 int /*<<< orphan*/  NSP_ETH_STATE_RATE ; 
 int /*<<< orphan*/  NSP_ETH_STATE_RX_ENABLED ; 
 int /*<<< orphan*/  NSP_ETH_STATE_TX_ENABLED ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_eth_copy_mac_reverse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int nfp_eth_rate2speed (int) ; 
 int nfp_nsp_get_abi_ver_minor (struct nfp_nsp*) ; 

__attribute__((used)) static void
nfp_eth_port_translate(struct nfp_nsp *nsp, const union eth_table_entry *src,
		       unsigned int index, struct nfp_eth_table_port *dst)
{
	unsigned int rate;
	unsigned int fec;
	u64 port, state;

	port = le64_to_cpu(src->port);
	state = le64_to_cpu(src->state);

	dst->eth_index = FIELD_GET(NSP_ETH_PORT_INDEX, port);
	dst->index = index;
	dst->nbi = index / NSP_ETH_NBI_PORT_COUNT;
	dst->base = index % NSP_ETH_NBI_PORT_COUNT;
	dst->lanes = FIELD_GET(NSP_ETH_PORT_LANES, port);

	dst->enabled = FIELD_GET(NSP_ETH_STATE_ENABLED, state);
	dst->tx_enabled = FIELD_GET(NSP_ETH_STATE_TX_ENABLED, state);
	dst->rx_enabled = FIELD_GET(NSP_ETH_STATE_RX_ENABLED, state);

	rate = nfp_eth_rate2speed(FIELD_GET(NSP_ETH_STATE_RATE, state));
	dst->speed = dst->lanes * rate;

	dst->interface = FIELD_GET(NSP_ETH_STATE_INTERFACE, state);
	dst->media = FIELD_GET(NSP_ETH_STATE_MEDIA, state);

	nfp_eth_copy_mac_reverse(dst->mac_addr, src->mac_addr);

	dst->label_port = FIELD_GET(NSP_ETH_PORT_PHYLABEL, port);
	dst->label_subport = FIELD_GET(NSP_ETH_PORT_LABEL, port);

	if (nfp_nsp_get_abi_ver_minor(nsp) < 17)
		return;

	dst->override_changed = FIELD_GET(NSP_ETH_STATE_OVRD_CHNG, state);
	dst->aneg = FIELD_GET(NSP_ETH_STATE_ANEG, state);

	if (nfp_nsp_get_abi_ver_minor(nsp) < 22)
		return;

	fec = FIELD_GET(NSP_ETH_PORT_FEC_SUPP_BASER, port);
	dst->fec_modes_supported |= fec << NFP_FEC_BASER_BIT;
	fec = FIELD_GET(NSP_ETH_PORT_FEC_SUPP_RS, port);
	dst->fec_modes_supported |= fec << NFP_FEC_REED_SOLOMON_BIT;
	if (dst->fec_modes_supported)
		dst->fec_modes_supported |= NFP_FEC_AUTO | NFP_FEC_DISABLED;

	dst->fec = 1 << FIELD_GET(NSP_ETH_STATE_FEC, state);
}