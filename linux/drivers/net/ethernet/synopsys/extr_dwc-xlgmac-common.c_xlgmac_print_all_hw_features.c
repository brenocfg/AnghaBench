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
struct TYPE_2__ {int ts_src; int rx_fifo_size; int tx_fifo_size; int pps_out_num; int aux_snap_num; int /*<<< orphan*/  tx_ch_cnt; int /*<<< orphan*/  rx_ch_cnt; int /*<<< orphan*/  tx_q_cnt; int /*<<< orphan*/  rx_q_cnt; int /*<<< orphan*/  l3l4_filter_num; int /*<<< orphan*/  hash_table_size; int /*<<< orphan*/  tc_cnt; scalar_t__ rss; scalar_t__ dma_debug; scalar_t__ tso; scalar_t__ sph; scalar_t__ dcb; int /*<<< orphan*/  dma_width; scalar_t__ adv_ts_hi; scalar_t__ sa_vlan_ins; scalar_t__ addn_mac; scalar_t__ rx_coe; scalar_t__ tx_coe; scalar_t__ eee; scalar_t__ ts; scalar_t__ aoe; scalar_t__ mmc; scalar_t__ mgk; scalar_t__ rwk; scalar_t__ sma; scalar_t__ vlhash; } ;
struct xlgmac_pdata {TYPE_1__ hw_feat; } ;

/* Variables and functions */
 int /*<<< orphan*/  XLGMAC_PR (char*,...) ; 

void xlgmac_print_all_hw_features(struct xlgmac_pdata *pdata)
{
	char *str = NULL;

	XLGMAC_PR("\n");
	XLGMAC_PR("=====================================================\n");
	XLGMAC_PR("\n");
	XLGMAC_PR("HW support following features\n");
	XLGMAC_PR("\n");
	/* HW Feature Register0 */
	XLGMAC_PR("VLAN Hash Filter Selected                   : %s\n",
		  pdata->hw_feat.vlhash ? "YES" : "NO");
	XLGMAC_PR("SMA (MDIO) Interface                        : %s\n",
		  pdata->hw_feat.sma ? "YES" : "NO");
	XLGMAC_PR("PMT Remote Wake-up Packet Enable            : %s\n",
		  pdata->hw_feat.rwk ? "YES" : "NO");
	XLGMAC_PR("PMT Magic Packet Enable                     : %s\n",
		  pdata->hw_feat.mgk ? "YES" : "NO");
	XLGMAC_PR("RMON/MMC Module Enable                      : %s\n",
		  pdata->hw_feat.mmc ? "YES" : "NO");
	XLGMAC_PR("ARP Offload Enabled                         : %s\n",
		  pdata->hw_feat.aoe ? "YES" : "NO");
	XLGMAC_PR("IEEE 1588-2008 Timestamp Enabled            : %s\n",
		  pdata->hw_feat.ts ? "YES" : "NO");
	XLGMAC_PR("Energy Efficient Ethernet Enabled           : %s\n",
		  pdata->hw_feat.eee ? "YES" : "NO");
	XLGMAC_PR("Transmit Checksum Offload Enabled           : %s\n",
		  pdata->hw_feat.tx_coe ? "YES" : "NO");
	XLGMAC_PR("Receive Checksum Offload Enabled            : %s\n",
		  pdata->hw_feat.rx_coe ? "YES" : "NO");
	XLGMAC_PR("Additional MAC Addresses 1-31 Selected      : %s\n",
		  pdata->hw_feat.addn_mac ? "YES" : "NO");

	switch (pdata->hw_feat.ts_src) {
	case 0:
		str = "RESERVED";
		break;
	case 1:
		str = "INTERNAL";
		break;
	case 2:
		str = "EXTERNAL";
		break;
	case 3:
		str = "BOTH";
		break;
	}
	XLGMAC_PR("Timestamp System Time Source                : %s\n", str);

	XLGMAC_PR("Source Address or VLAN Insertion Enable     : %s\n",
		  pdata->hw_feat.sa_vlan_ins ? "YES" : "NO");

	/* HW Feature Register1 */
	switch (pdata->hw_feat.rx_fifo_size) {
	case 0:
		str = "128 bytes";
		break;
	case 1:
		str = "256 bytes";
		break;
	case 2:
		str = "512 bytes";
		break;
	case 3:
		str = "1 KBytes";
		break;
	case 4:
		str = "2 KBytes";
		break;
	case 5:
		str = "4 KBytes";
		break;
	case 6:
		str = "8 KBytes";
		break;
	case 7:
		str = "16 KBytes";
		break;
	case 8:
		str = "32 kBytes";
		break;
	case 9:
		str = "64 KBytes";
		break;
	case 10:
		str = "128 KBytes";
		break;
	case 11:
		str = "256 KBytes";
		break;
	default:
		str = "RESERVED";
	}
	XLGMAC_PR("MTL Receive FIFO Size                       : %s\n", str);

	switch (pdata->hw_feat.tx_fifo_size) {
	case 0:
		str = "128 bytes";
		break;
	case 1:
		str = "256 bytes";
		break;
	case 2:
		str = "512 bytes";
		break;
	case 3:
		str = "1 KBytes";
		break;
	case 4:
		str = "2 KBytes";
		break;
	case 5:
		str = "4 KBytes";
		break;
	case 6:
		str = "8 KBytes";
		break;
	case 7:
		str = "16 KBytes";
		break;
	case 8:
		str = "32 kBytes";
		break;
	case 9:
		str = "64 KBytes";
		break;
	case 10:
		str = "128 KBytes";
		break;
	case 11:
		str = "256 KBytes";
		break;
	default:
		str = "RESERVED";
	}
	XLGMAC_PR("MTL Transmit FIFO Size                      : %s\n", str);

	XLGMAC_PR("IEEE 1588 High Word Register Enable         : %s\n",
		  pdata->hw_feat.adv_ts_hi ? "YES" : "NO");
	XLGMAC_PR("Address width                               : %u\n",
		  pdata->hw_feat.dma_width);
	XLGMAC_PR("DCB Feature Enable                          : %s\n",
		  pdata->hw_feat.dcb ? "YES" : "NO");
	XLGMAC_PR("Split Header Feature Enable                 : %s\n",
		  pdata->hw_feat.sph ? "YES" : "NO");
	XLGMAC_PR("TCP Segmentation Offload Enable             : %s\n",
		  pdata->hw_feat.tso ? "YES" : "NO");
	XLGMAC_PR("DMA Debug Registers Enabled                 : %s\n",
		  pdata->hw_feat.dma_debug ? "YES" : "NO");
	XLGMAC_PR("RSS Feature Enabled                         : %s\n",
		  pdata->hw_feat.rss ? "YES" : "NO");
	XLGMAC_PR("Number of Traffic classes                   : %u\n",
		  (pdata->hw_feat.tc_cnt));
	XLGMAC_PR("Hash Table Size                             : %u\n",
		  pdata->hw_feat.hash_table_size);
	XLGMAC_PR("Total number of L3 or L4 Filters            : %u\n",
		  pdata->hw_feat.l3l4_filter_num);

	/* HW Feature Register2 */
	XLGMAC_PR("Number of MTL Receive Queues                : %u\n",
		  pdata->hw_feat.rx_q_cnt);
	XLGMAC_PR("Number of MTL Transmit Queues               : %u\n",
		  pdata->hw_feat.tx_q_cnt);
	XLGMAC_PR("Number of DMA Receive Channels              : %u\n",
		  pdata->hw_feat.rx_ch_cnt);
	XLGMAC_PR("Number of DMA Transmit Channels             : %u\n",
		  pdata->hw_feat.tx_ch_cnt);

	switch (pdata->hw_feat.pps_out_num) {
	case 0:
		str = "No PPS output";
		break;
	case 1:
		str = "1 PPS output";
		break;
	case 2:
		str = "2 PPS output";
		break;
	case 3:
		str = "3 PPS output";
		break;
	case 4:
		str = "4 PPS output";
		break;
	default:
		str = "RESERVED";
	}
	XLGMAC_PR("Number of PPS Outputs                       : %s\n", str);

	switch (pdata->hw_feat.aux_snap_num) {
	case 0:
		str = "No auxiliary input";
		break;
	case 1:
		str = "1 auxiliary input";
		break;
	case 2:
		str = "2 auxiliary input";
		break;
	case 3:
		str = "3 auxiliary input";
		break;
	case 4:
		str = "4 auxiliary input";
		break;
	default:
		str = "RESERVED";
	}
	XLGMAC_PR("Number of Auxiliary Snapshot Inputs         : %s", str);

	XLGMAC_PR("\n");
	XLGMAC_PR("=====================================================\n");
	XLGMAC_PR("\n");
}