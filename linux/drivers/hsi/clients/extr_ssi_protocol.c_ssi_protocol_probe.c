#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ssi_protocol {int channel_id_cmd; int channel_id_data; TYPE_1__* netdev; int /*<<< orphan*/  link; int /*<<< orphan*/  work; struct hsi_client* cl; int /*<<< orphan*/  tx_usecnt; int /*<<< orphan*/  cmdqueue; int /*<<< orphan*/  txqueue; int /*<<< orphan*/  keep_alive; int /*<<< orphan*/  tx_wd; int /*<<< orphan*/  rx_wd; int /*<<< orphan*/  lock; } ;
struct hsi_client {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  min_mtu; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 int /*<<< orphan*/  PHONET_MIN_MTU ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (TYPE_1__*,struct device*) ; 
 int /*<<< orphan*/  SSIP_MAX_MTU ; 
 int /*<<< orphan*/  TIMER_DEFERRABLE ; 
 TYPE_1__* alloc_netdev (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  free_netdev (TYPE_1__*) ; 
 int /*<<< orphan*/  hsi_client_set_drvdata (struct hsi_client*,struct ssi_protocol*) ; 
 void* hsi_get_channel_id_by_name (struct hsi_client*,char*) ; 
 int /*<<< orphan*/  kfree (struct ssi_protocol*) ; 
 struct ssi_protocol* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (TYPE_1__*) ; 
 int register_netdev (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int ssip_alloc_cmds (struct ssi_protocol*) ; 
 int /*<<< orphan*/  ssip_free_cmds (struct ssi_protocol*) ; 
 int /*<<< orphan*/  ssip_keep_alive ; 
 int /*<<< orphan*/  ssip_list ; 
 int /*<<< orphan*/  ssip_pn_setup ; 
 int /*<<< orphan*/  ssip_rx_wd ; 
 int /*<<< orphan*/  ssip_tx_wd ; 
 int /*<<< orphan*/  ssip_xmit_work ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hsi_client* to_hsi_client (struct device*) ; 

__attribute__((used)) static int ssi_protocol_probe(struct device *dev)
{
	static const char ifname[] = "phonet%d";
	struct hsi_client *cl = to_hsi_client(dev);
	struct ssi_protocol *ssi;
	int err;

	ssi = kzalloc(sizeof(*ssi), GFP_KERNEL);
	if (!ssi)
		return -ENOMEM;

	spin_lock_init(&ssi->lock);
	timer_setup(&ssi->rx_wd, ssip_rx_wd, TIMER_DEFERRABLE);
	timer_setup(&ssi->tx_wd, ssip_tx_wd, TIMER_DEFERRABLE);
	timer_setup(&ssi->keep_alive, ssip_keep_alive, 0);
	INIT_LIST_HEAD(&ssi->txqueue);
	INIT_LIST_HEAD(&ssi->cmdqueue);
	atomic_set(&ssi->tx_usecnt, 0);
	hsi_client_set_drvdata(cl, ssi);
	ssi->cl = cl;
	INIT_WORK(&ssi->work, ssip_xmit_work);

	ssi->channel_id_cmd = hsi_get_channel_id_by_name(cl, "mcsaab-control");
	if (ssi->channel_id_cmd < 0) {
		err = ssi->channel_id_cmd;
		dev_err(dev, "Could not get cmd channel (%d)\n", err);
		goto out;
	}

	ssi->channel_id_data = hsi_get_channel_id_by_name(cl, "mcsaab-data");
	if (ssi->channel_id_data < 0) {
		err = ssi->channel_id_data;
		dev_err(dev, "Could not get data channel (%d)\n", err);
		goto out;
	}

	err = ssip_alloc_cmds(ssi);
	if (err < 0) {
		dev_err(dev, "No memory for commands\n");
		goto out;
	}

	ssi->netdev = alloc_netdev(0, ifname, NET_NAME_UNKNOWN, ssip_pn_setup);
	if (!ssi->netdev) {
		dev_err(dev, "No memory for netdev\n");
		err = -ENOMEM;
		goto out1;
	}

	/* MTU range: 6 - 65535 */
	ssi->netdev->min_mtu = PHONET_MIN_MTU;
	ssi->netdev->max_mtu = SSIP_MAX_MTU;

	SET_NETDEV_DEV(ssi->netdev, dev);
	netif_carrier_off(ssi->netdev);
	err = register_netdev(ssi->netdev);
	if (err < 0) {
		dev_err(dev, "Register netdev failed (%d)\n", err);
		goto out2;
	}

	list_add(&ssi->link, &ssip_list);

	dev_dbg(dev, "channel configuration: cmd=%d, data=%d\n",
		ssi->channel_id_cmd, ssi->channel_id_data);

	return 0;
out2:
	free_netdev(ssi->netdev);
out1:
	ssip_free_cmds(ssi);
out:
	kfree(ssi);

	return err;
}