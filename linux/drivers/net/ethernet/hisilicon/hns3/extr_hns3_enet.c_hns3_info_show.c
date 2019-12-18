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
struct hns3_nic_priv {TYPE_2__* netdev; int /*<<< orphan*/  dev; TYPE_1__* ae_handle; } ;
struct hnae3_knic_private_info {int /*<<< orphan*/  num_tc; int /*<<< orphan*/  num_rx_desc; int /*<<< orphan*/  num_tx_desc; int /*<<< orphan*/  rx_buf_len; int /*<<< orphan*/  req_rss_size; int /*<<< orphan*/  rss_size; int /*<<< orphan*/  num_tqps; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_3__ {struct hnae3_knic_private_info kinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns3_info_show(struct hns3_nic_priv *priv)
{
	struct hnae3_knic_private_info *kinfo = &priv->ae_handle->kinfo;

	dev_info(priv->dev, "MAC address: %pM\n", priv->netdev->dev_addr);
	dev_info(priv->dev, "Task queue pairs numbers: %d\n", kinfo->num_tqps);
	dev_info(priv->dev, "RSS size: %d\n", kinfo->rss_size);
	dev_info(priv->dev, "Allocated RSS size: %d\n", kinfo->req_rss_size);
	dev_info(priv->dev, "RX buffer length: %d\n", kinfo->rx_buf_len);
	dev_info(priv->dev, "Desc num per TX queue: %d\n", kinfo->num_tx_desc);
	dev_info(priv->dev, "Desc num per RX queue: %d\n", kinfo->num_rx_desc);
	dev_info(priv->dev, "Total number of enabled TCs: %d\n", kinfo->num_tc);
	dev_info(priv->dev, "Max mtu size: %d\n", priv->netdev->max_mtu);
}