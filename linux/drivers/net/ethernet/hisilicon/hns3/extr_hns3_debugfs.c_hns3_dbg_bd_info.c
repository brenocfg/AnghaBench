#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct hns3_nic_ring_data {struct hns3_enet_ring* ring; } ;
struct hns3_nic_priv {struct hns3_nic_ring_data* ring_data; } ;
struct hns3_enet_ring {size_t desc_num; struct hns3_desc* desc; TYPE_4__* tqp; } ;
struct TYPE_10__ {int /*<<< orphan*/ * bd_base_info; int /*<<< orphan*/ * ot_vlan_tag; int /*<<< orphan*/ * o_dm_vlan_id_fb; int /*<<< orphan*/ * vlan_tag; int /*<<< orphan*/ * fd_id; int /*<<< orphan*/ * rss_hash; int /*<<< orphan*/ * size; int /*<<< orphan*/ * pkt_len; int /*<<< orphan*/ * l234_info; } ;
struct TYPE_7__ {int /*<<< orphan*/ * mss; int /*<<< orphan*/ * bdtp_fe_sc_vld_ra_ri; int /*<<< orphan*/ * paylen; int /*<<< orphan*/ * ol4_len; int /*<<< orphan*/ * ol3_len; int /*<<< orphan*/ * ol2_len; int /*<<< orphan*/ * ol_type_vlan_msec; int /*<<< orphan*/ * tv; int /*<<< orphan*/ * outer_vlan_tag; int /*<<< orphan*/ * l4_len; int /*<<< orphan*/ * l3_len; int /*<<< orphan*/ * l2_len; int /*<<< orphan*/ * type_cs_vlan_tso; int /*<<< orphan*/ * send_size; int /*<<< orphan*/ * vlan_tag; } ;
struct hns3_desc {TYPE_5__ rx; int /*<<< orphan*/  addr; TYPE_2__ tx; } ;
struct TYPE_8__ {size_t num_tqps; } ;
struct hnae3_handle {TYPE_3__ kinfo; TYPE_1__* pdev; struct hns3_nic_priv* priv; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_9__ {scalar_t__ io_base; } ;
struct TYPE_6__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HNS3_RING_RX_RING_TAIL_REG ; 
 scalar_t__ HNS3_RING_TX_RING_TAIL_REG ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,size_t,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,size_t,...) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 size_t readl_relaxed (scalar_t__) ; 
 int sscanf (char const*,char*,size_t*,size_t*) ; 

__attribute__((used)) static int hns3_dbg_bd_info(struct hnae3_handle *h, const char *cmd_buf)
{
	struct hns3_nic_priv *priv = h->priv;
	struct hns3_nic_ring_data *ring_data;
	struct hns3_desc *rx_desc, *tx_desc;
	struct device *dev = &h->pdev->dev;
	struct hns3_enet_ring *ring;
	u32 tx_index, rx_index;
	u32 q_num, value;
	dma_addr_t addr;
	int cnt;

	cnt = sscanf(&cmd_buf[8], "%u %u", &q_num, &tx_index);
	if (cnt == 2) {
		rx_index = tx_index;
	} else if (cnt != 1) {
		dev_err(dev, "bd info: bad command string, cnt=%d\n", cnt);
		return -EINVAL;
	}

	if (q_num >= h->kinfo.num_tqps) {
		dev_err(dev, "Queue number(%u) is out of range(0-%u)\n", q_num,
			h->kinfo.num_tqps - 1);
		return -EINVAL;
	}

	ring_data = priv->ring_data;
	ring  = ring_data[q_num].ring;
	value = readl_relaxed(ring->tqp->io_base + HNS3_RING_TX_RING_TAIL_REG);
	tx_index = (cnt == 1) ? value : tx_index;

	if (tx_index >= ring->desc_num) {
		dev_err(dev, "bd index(%u) is out of range(0-%u)\n", tx_index,
			ring->desc_num - 1);
		return -EINVAL;
	}

	tx_desc = &ring->desc[tx_index];
	addr = le64_to_cpu(tx_desc->addr);
	dev_info(dev, "TX Queue Num: %u, BD Index: %u\n", q_num, tx_index);
	dev_info(dev, "(TX)addr: %pad\n", &addr);
	dev_info(dev, "(TX)vlan_tag: %u\n", tx_desc->tx.vlan_tag);
	dev_info(dev, "(TX)send_size: %u\n", tx_desc->tx.send_size);
	dev_info(dev, "(TX)vlan_tso: %u\n", tx_desc->tx.type_cs_vlan_tso);
	dev_info(dev, "(TX)l2_len: %u\n", tx_desc->tx.l2_len);
	dev_info(dev, "(TX)l3_len: %u\n", tx_desc->tx.l3_len);
	dev_info(dev, "(TX)l4_len: %u\n", tx_desc->tx.l4_len);
	dev_info(dev, "(TX)vlan_tag: %u\n", tx_desc->tx.outer_vlan_tag);
	dev_info(dev, "(TX)tv: %u\n", tx_desc->tx.tv);
	dev_info(dev, "(TX)vlan_msec: %u\n", tx_desc->tx.ol_type_vlan_msec);
	dev_info(dev, "(TX)ol2_len: %u\n", tx_desc->tx.ol2_len);
	dev_info(dev, "(TX)ol3_len: %u\n", tx_desc->tx.ol3_len);
	dev_info(dev, "(TX)ol4_len: %u\n", tx_desc->tx.ol4_len);
	dev_info(dev, "(TX)paylen: %u\n", tx_desc->tx.paylen);
	dev_info(dev, "(TX)vld_ra_ri: %u\n", tx_desc->tx.bdtp_fe_sc_vld_ra_ri);
	dev_info(dev, "(TX)mss: %u\n", tx_desc->tx.mss);

	ring  = ring_data[q_num + h->kinfo.num_tqps].ring;
	value = readl_relaxed(ring->tqp->io_base + HNS3_RING_RX_RING_TAIL_REG);
	rx_index = (cnt == 1) ? value : tx_index;
	rx_desc	 = &ring->desc[rx_index];

	addr = le64_to_cpu(rx_desc->addr);
	dev_info(dev, "RX Queue Num: %u, BD Index: %u\n", q_num, rx_index);
	dev_info(dev, "(RX)addr: %pad\n", &addr);
	dev_info(dev, "(RX)l234_info: %u\n", rx_desc->rx.l234_info);
	dev_info(dev, "(RX)pkt_len: %u\n", rx_desc->rx.pkt_len);
	dev_info(dev, "(RX)size: %u\n", rx_desc->rx.size);
	dev_info(dev, "(RX)rss_hash: %u\n", rx_desc->rx.rss_hash);
	dev_info(dev, "(RX)fd_id: %u\n", rx_desc->rx.fd_id);
	dev_info(dev, "(RX)vlan_tag: %u\n", rx_desc->rx.vlan_tag);
	dev_info(dev, "(RX)o_dm_vlan_id_fb: %u\n", rx_desc->rx.o_dm_vlan_id_fb);
	dev_info(dev, "(RX)ot_vlan_tag: %u\n", rx_desc->rx.ot_vlan_tag);
	dev_info(dev, "(RX)bd_base_info: %u\n", rx_desc->rx.bd_base_info);

	return 0;
}