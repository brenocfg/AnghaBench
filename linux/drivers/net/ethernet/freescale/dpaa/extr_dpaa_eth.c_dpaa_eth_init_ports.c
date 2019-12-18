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
struct mac_device {struct fman_port** port; } ;
struct fman_port {int dummy; } ;
struct fm_port_fqs {int /*<<< orphan*/  rx_pcdq; int /*<<< orphan*/  rx_defq; int /*<<< orphan*/  rx_errq; int /*<<< orphan*/  tx_defq; int /*<<< orphan*/  tx_errq; } ;
struct dpaa_buffer_layout {int dummy; } ;
struct dpaa_bp {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 size_t RX ; 
 size_t TX ; 
 int dpaa_eth_init_rx_port (struct fman_port*,struct dpaa_bp**,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpaa_buffer_layout*) ; 
 int dpaa_eth_init_tx_port (struct fman_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpaa_buffer_layout*) ; 

__attribute__((used)) static int dpaa_eth_init_ports(struct mac_device *mac_dev,
			       struct dpaa_bp **bps, size_t count,
			       struct fm_port_fqs *port_fqs,
			       struct dpaa_buffer_layout *buf_layout,
			       struct device *dev)
{
	struct fman_port *rxport = mac_dev->port[RX];
	struct fman_port *txport = mac_dev->port[TX];
	int err;

	err = dpaa_eth_init_tx_port(txport, port_fqs->tx_errq,
				    port_fqs->tx_defq, &buf_layout[TX]);
	if (err)
		return err;

	err = dpaa_eth_init_rx_port(rxport, bps, count, port_fqs->rx_errq,
				    port_fqs->rx_defq, port_fqs->rx_pcdq,
				    &buf_layout[RX]);

	return err;
}