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
struct niu_parent {int num_ports; int* rxchan_per_port; int* txchan_per_port; int /*<<< orphan*/  index; int /*<<< orphan*/  port_phy; } ;

/* Variables and functions */
 int NIU_NUM_RXCHAN ; 
 int NIU_NUM_TXCHAN ; 
 int PORT_TYPE_10G ; 
 int phy_decode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void niu_divide_channels(struct niu_parent *parent,
				int num_10g, int num_1g)
{
	int num_ports = parent->num_ports;
	int rx_chans_per_10g, rx_chans_per_1g;
	int tx_chans_per_10g, tx_chans_per_1g;
	int i, tot_rx, tot_tx;

	if (!num_10g || !num_1g) {
		rx_chans_per_10g = rx_chans_per_1g =
			(NIU_NUM_RXCHAN / num_ports);
		tx_chans_per_10g = tx_chans_per_1g =
			(NIU_NUM_TXCHAN / num_ports);
	} else {
		rx_chans_per_1g = NIU_NUM_RXCHAN / 8;
		rx_chans_per_10g = (NIU_NUM_RXCHAN -
				    (rx_chans_per_1g * num_1g)) /
			num_10g;

		tx_chans_per_1g = NIU_NUM_TXCHAN / 6;
		tx_chans_per_10g = (NIU_NUM_TXCHAN -
				    (tx_chans_per_1g * num_1g)) /
			num_10g;
	}

	tot_rx = tot_tx = 0;
	for (i = 0; i < num_ports; i++) {
		int type = phy_decode(parent->port_phy, i);

		if (type == PORT_TYPE_10G) {
			parent->rxchan_per_port[i] = rx_chans_per_10g;
			parent->txchan_per_port[i] = tx_chans_per_10g;
		} else {
			parent->rxchan_per_port[i] = rx_chans_per_1g;
			parent->txchan_per_port[i] = tx_chans_per_1g;
		}
		pr_info("niu%d: Port %u [%u RX chans] [%u TX chans]\n",
			parent->index, i,
			parent->rxchan_per_port[i],
			parent->txchan_per_port[i]);
		tot_rx += parent->rxchan_per_port[i];
		tot_tx += parent->txchan_per_port[i];
	}

	if (tot_rx > NIU_NUM_RXCHAN) {
		pr_err("niu%d: Too many RX channels (%d), resetting to one per port\n",
		       parent->index, tot_rx);
		for (i = 0; i < num_ports; i++)
			parent->rxchan_per_port[i] = 1;
	}
	if (tot_tx > NIU_NUM_TXCHAN) {
		pr_err("niu%d: Too many TX channels (%d), resetting to one per port\n",
		       parent->index, tot_tx);
		for (i = 0; i < num_ports; i++)
			parent->txchan_per_port[i] = 1;
	}
	if (tot_rx < NIU_NUM_RXCHAN || tot_tx < NIU_NUM_TXCHAN) {
		pr_warn("niu%d: Driver bug, wasted channels, RX[%d] TX[%d]\n",
			parent->index, tot_rx, tot_tx);
	}
}