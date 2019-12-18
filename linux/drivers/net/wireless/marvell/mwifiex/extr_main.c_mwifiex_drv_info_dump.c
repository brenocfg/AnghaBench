#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_card_rec {int /*<<< orphan*/  rx_data_urb_pending; int /*<<< orphan*/  rx_cmd_urb_pending; TYPE_2__* port; int /*<<< orphan*/  tx_cmd_urb_pending; } ;
struct sdio_mmc_card {int mp_rd_bitmap; int curr_rd_port; int mp_wr_bitmap; int curr_wr_port; } ;
struct netdev_queue {int dummy; } ;
struct mwifiex_private {int num_tx_timeout; TYPE_3__* netdev; int /*<<< orphan*/  media_connected; int /*<<< orphan*/ * wmm_tx_pending; } ;
struct mwifiex_debug_info {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* reg_dump ) (struct mwifiex_adapter*,char*) ;} ;
struct mwifiex_adapter {char* devdump_data; scalar_t__ iface_type; int priv_num; int devdump_len; struct mwifiex_private** priv; TYPE_1__ if_ops; scalar_t__ card; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_pending; } ;
typedef  int /*<<< orphan*/  drv_version ;
struct TYPE_7__ {char* name; int num_tx_queues; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_data_urb_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MSG ; 
 scalar_t__ MWIFIEX_PCIE ; 
 scalar_t__ MWIFIEX_SDIO ; 
 scalar_t__ MWIFIEX_USB ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mwifiex_debug_info*) ; 
 struct mwifiex_debug_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mwifiex_debug_info_to_buffer (struct mwifiex_private*,char*,struct mwifiex_debug_info*) ; 
 int /*<<< orphan*/  mwifiex_drv_get_driver_version (struct mwifiex_adapter*,char*,int) ; 
 int /*<<< orphan*/  mwifiex_get_debug_info (struct mwifiex_private*,struct mwifiex_debug_info*) ; 
 struct netdev_queue* netdev_get_tx_queue (TYPE_3__*,int) ; 
 scalar_t__ netif_carrier_ok (TYPE_3__*) ; 
 scalar_t__ netif_tx_queue_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  stub1 (struct mwifiex_adapter*,char*) ; 

void mwifiex_drv_info_dump(struct mwifiex_adapter *adapter)
{
	char *p;
	char drv_version[64];
	struct usb_card_rec *cardp;
	struct sdio_mmc_card *sdio_card;
	struct mwifiex_private *priv;
	int i, idx;
	struct netdev_queue *txq;
	struct mwifiex_debug_info *debug_info;

	mwifiex_dbg(adapter, MSG, "===mwifiex driverinfo dump start===\n");

	p = adapter->devdump_data;
	strcpy(p, "========Start dump driverinfo========\n");
	p += strlen("========Start dump driverinfo========\n");
	p += sprintf(p, "driver_name = " "\"mwifiex\"\n");

	mwifiex_drv_get_driver_version(adapter, drv_version,
				       sizeof(drv_version) - 1);
	p += sprintf(p, "driver_version = %s\n", drv_version);

	if (adapter->iface_type == MWIFIEX_USB) {
		cardp = (struct usb_card_rec *)adapter->card;
		p += sprintf(p, "tx_cmd_urb_pending = %d\n",
			     atomic_read(&cardp->tx_cmd_urb_pending));
		p += sprintf(p, "tx_data_urb_pending_port_0 = %d\n",
			     atomic_read(&cardp->port[0].tx_data_urb_pending));
		p += sprintf(p, "tx_data_urb_pending_port_1 = %d\n",
			     atomic_read(&cardp->port[1].tx_data_urb_pending));
		p += sprintf(p, "rx_cmd_urb_pending = %d\n",
			     atomic_read(&cardp->rx_cmd_urb_pending));
		p += sprintf(p, "rx_data_urb_pending = %d\n",
			     atomic_read(&cardp->rx_data_urb_pending));
	}

	p += sprintf(p, "tx_pending = %d\n",
		     atomic_read(&adapter->tx_pending));
	p += sprintf(p, "rx_pending = %d\n",
		     atomic_read(&adapter->rx_pending));

	if (adapter->iface_type == MWIFIEX_SDIO) {
		sdio_card = (struct sdio_mmc_card *)adapter->card;
		p += sprintf(p, "\nmp_rd_bitmap=0x%x curr_rd_port=0x%x\n",
			     sdio_card->mp_rd_bitmap, sdio_card->curr_rd_port);
		p += sprintf(p, "mp_wr_bitmap=0x%x curr_wr_port=0x%x\n",
			     sdio_card->mp_wr_bitmap, sdio_card->curr_wr_port);
	}

	for (i = 0; i < adapter->priv_num; i++) {
		if (!adapter->priv[i] || !adapter->priv[i]->netdev)
			continue;
		priv = adapter->priv[i];
		p += sprintf(p, "\n[interface  : \"%s\"]\n",
			     priv->netdev->name);
		p += sprintf(p, "wmm_tx_pending[0] = %d\n",
			     atomic_read(&priv->wmm_tx_pending[0]));
		p += sprintf(p, "wmm_tx_pending[1] = %d\n",
			     atomic_read(&priv->wmm_tx_pending[1]));
		p += sprintf(p, "wmm_tx_pending[2] = %d\n",
			     atomic_read(&priv->wmm_tx_pending[2]));
		p += sprintf(p, "wmm_tx_pending[3] = %d\n",
			     atomic_read(&priv->wmm_tx_pending[3]));
		p += sprintf(p, "media_state=\"%s\"\n", !priv->media_connected ?
			     "Disconnected" : "Connected");
		p += sprintf(p, "carrier %s\n", (netif_carrier_ok(priv->netdev)
			     ? "on" : "off"));
		for (idx = 0; idx < priv->netdev->num_tx_queues; idx++) {
			txq = netdev_get_tx_queue(priv->netdev, idx);
			p += sprintf(p, "tx queue %d:%s  ", idx,
				     netif_tx_queue_stopped(txq) ?
				     "stopped" : "started");
		}
		p += sprintf(p, "\n%s: num_tx_timeout = %d\n",
			     priv->netdev->name, priv->num_tx_timeout);
	}

	if (adapter->iface_type == MWIFIEX_SDIO ||
	    adapter->iface_type == MWIFIEX_PCIE) {
		p += sprintf(p, "\n=== %s register dump===\n",
			     adapter->iface_type == MWIFIEX_SDIO ?
							"SDIO" : "PCIE");
		if (adapter->if_ops.reg_dump)
			p += adapter->if_ops.reg_dump(adapter, p);
	}
	p += sprintf(p, "\n=== more debug information\n");
	debug_info = kzalloc(sizeof(*debug_info), GFP_KERNEL);
	if (debug_info) {
		for (i = 0; i < adapter->priv_num; i++) {
			if (!adapter->priv[i] || !adapter->priv[i]->netdev)
				continue;
			priv = adapter->priv[i];
			mwifiex_get_debug_info(priv, debug_info);
			p += mwifiex_debug_info_to_buffer(priv, p, debug_info);
			break;
		}
		kfree(debug_info);
	}

	strcpy(p, "\n========End dump========\n");
	p += strlen("\n========End dump========\n");
	mwifiex_dbg(adapter, MSG, "===mwifiex driverinfo dump end===\n");
	adapter->devdump_len = p - (char *)adapter->devdump_data;
}