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
struct dsaf_device {int /*<<< orphan*/  dsaf_ver; } ;

/* Variables and functions */
 int AE_IS_VER1 (int /*<<< orphan*/ ) ; 
 int DSAF_PRIO_NR ; 
 int DSAF_SERVICE_NW_NUM ; 
 int ETH_GSTRING_LEN ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,...) ; 

__attribute__((used)) static char *hns_dsaf_get_node_stats_strings(char *data, int node,
					     struct dsaf_device *dsaf_dev)
{
	char *buff = data;
	int i;
	bool is_ver1 = AE_IS_VER1(dsaf_dev->dsaf_ver);

	snprintf(buff, ETH_GSTRING_LEN, "innod%d_pad_drop_pkts", node);
	buff += ETH_GSTRING_LEN;
	snprintf(buff, ETH_GSTRING_LEN, "innod%d_manage_pkts", node);
	buff += ETH_GSTRING_LEN;
	snprintf(buff, ETH_GSTRING_LEN, "innod%d_rx_pkts", node);
	buff += ETH_GSTRING_LEN;
	snprintf(buff, ETH_GSTRING_LEN, "innod%d_rx_pkt_id", node);
	buff += ETH_GSTRING_LEN;
	snprintf(buff, ETH_GSTRING_LEN, "innod%d_rx_pause_frame", node);
	buff += ETH_GSTRING_LEN;
	snprintf(buff, ETH_GSTRING_LEN, "innod%d_release_buf_num", node);
	buff += ETH_GSTRING_LEN;
	snprintf(buff, ETH_GSTRING_LEN, "innod%d_sbm_drop_pkts", node);
	buff += ETH_GSTRING_LEN;
	snprintf(buff, ETH_GSTRING_LEN, "innod%d_crc_false_pkts", node);
	buff += ETH_GSTRING_LEN;
	snprintf(buff, ETH_GSTRING_LEN, "innod%d_bp_drop_pkts", node);
	buff += ETH_GSTRING_LEN;
	snprintf(buff, ETH_GSTRING_LEN, "innod%d_lookup_rslt_drop_pkts", node);
	buff += ETH_GSTRING_LEN;
	snprintf(buff, ETH_GSTRING_LEN, "innod%d_local_rslt_fail_pkts", node);
	buff += ETH_GSTRING_LEN;
	snprintf(buff, ETH_GSTRING_LEN, "innod%d_vlan_drop_pkts", node);
	buff += ETH_GSTRING_LEN;
	snprintf(buff, ETH_GSTRING_LEN, "innod%d_stp_drop_pkts", node);
	buff += ETH_GSTRING_LEN;
	if (node < DSAF_SERVICE_NW_NUM && !is_ver1) {
		for (i = 0; i < DSAF_PRIO_NR; i++) {
			snprintf(buff + 0 * ETH_GSTRING_LEN * DSAF_PRIO_NR,
				 ETH_GSTRING_LEN, "inod%d_pfc_prio%d_pkts",
				 node, i);
			snprintf(buff + 1 * ETH_GSTRING_LEN * DSAF_PRIO_NR,
				 ETH_GSTRING_LEN, "onod%d_pfc_prio%d_pkts",
				 node, i);
			buff += ETH_GSTRING_LEN;
		}
		buff += 1 * DSAF_PRIO_NR * ETH_GSTRING_LEN;
	}
	snprintf(buff, ETH_GSTRING_LEN, "onnod%d_tx_pkts", node);
	buff += ETH_GSTRING_LEN;

	return buff;
}