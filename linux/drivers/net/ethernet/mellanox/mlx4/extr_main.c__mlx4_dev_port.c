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
struct mlx4_port_cap {int /*<<< orphan*/  trans_code; int /*<<< orphan*/  wavelength; int /*<<< orphan*/  vendor_oui; int /*<<< orphan*/  trans_type; int /*<<< orphan*/  default_sense; int /*<<< orphan*/  suggested_type; int /*<<< orphan*/  supported_port_types; int /*<<< orphan*/  def_mac; int /*<<< orphan*/  max_tc_eth; int /*<<< orphan*/  eth_mtu; int /*<<< orphan*/  max_port_width; int /*<<< orphan*/  max_pkeys; int /*<<< orphan*/  max_gids; int /*<<< orphan*/  ib_mtu; int /*<<< orphan*/  max_vl; } ;
struct TYPE_4__ {int /*<<< orphan*/ * trans_code; int /*<<< orphan*/ * wavelength; int /*<<< orphan*/ * vendor_oui; int /*<<< orphan*/ * trans_type; int /*<<< orphan*/ * default_sense; int /*<<< orphan*/ * suggested_type; int /*<<< orphan*/ * supported_type; int /*<<< orphan*/ * def_mac; int /*<<< orphan*/  max_tc_eth; int /*<<< orphan*/ * eth_mtu_cap; int /*<<< orphan*/ * port_width_cap; int /*<<< orphan*/ * pkey_table_len; int /*<<< orphan*/ * gid_table_len; int /*<<< orphan*/ * ib_mtu_cap; int /*<<< orphan*/ * vl_cap; } ;
struct TYPE_3__ {int /*<<< orphan*/ * pkey_phys_table_len; int /*<<< orphan*/ * gid_phys_table_len; } ;
struct mlx4_dev {TYPE_2__ caps; TYPE_1__ phys_caps; } ;

/* Variables and functions */

__attribute__((used)) static int _mlx4_dev_port(struct mlx4_dev *dev, int port,
			  struct mlx4_port_cap *port_cap)
{
	dev->caps.vl_cap[port]	    = port_cap->max_vl;
	dev->caps.ib_mtu_cap[port]	    = port_cap->ib_mtu;
	dev->phys_caps.gid_phys_table_len[port]  = port_cap->max_gids;
	dev->phys_caps.pkey_phys_table_len[port] = port_cap->max_pkeys;
	/* set gid and pkey table operating lengths by default
	 * to non-sriov values
	 */
	dev->caps.gid_table_len[port]  = port_cap->max_gids;
	dev->caps.pkey_table_len[port] = port_cap->max_pkeys;
	dev->caps.port_width_cap[port] = port_cap->max_port_width;
	dev->caps.eth_mtu_cap[port]    = port_cap->eth_mtu;
	dev->caps.max_tc_eth	       = port_cap->max_tc_eth;
	dev->caps.def_mac[port]        = port_cap->def_mac;
	dev->caps.supported_type[port] = port_cap->supported_port_types;
	dev->caps.suggested_type[port] = port_cap->suggested_type;
	dev->caps.default_sense[port] = port_cap->default_sense;
	dev->caps.trans_type[port]	    = port_cap->trans_type;
	dev->caps.vendor_oui[port]     = port_cap->vendor_oui;
	dev->caps.wavelength[port]     = port_cap->wavelength;
	dev->caps.trans_code[port]     = port_cap->trans_code;

	return 0;
}