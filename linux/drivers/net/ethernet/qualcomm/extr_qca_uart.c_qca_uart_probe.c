#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct serdev_device {TYPE_1__ dev; } ;
struct qcauart {int /*<<< orphan*/  tx_work; struct net_device* net_dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  frm_handle; struct serdev_device* serdev; } ;
struct net_device {int dev_addr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (char const*) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,TYPE_1__*) ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ether_addr_copy (int,char const*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int) ; 
 struct qcauart* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 char* of_get_mac_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  qca_serdev_ops ; 
 int /*<<< orphan*/  qcafrm_fsm_init_uart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcauart_netdev_setup (struct net_device*) ; 
 int /*<<< orphan*/  qcauart_transmit ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  serdev_device_close (struct serdev_device*) ; 
 int serdev_device_open (struct serdev_device*) ; 
 int serdev_device_set_baudrate (struct serdev_device*,int) ; 
 int /*<<< orphan*/  serdev_device_set_client_ops (struct serdev_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serdev_device_set_drvdata (struct serdev_device*,struct qcauart*) ; 
 int /*<<< orphan*/  serdev_device_set_flow_control (struct serdev_device*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qca_uart_probe(struct serdev_device *serdev)
{
	struct net_device *qcauart_dev = alloc_etherdev(sizeof(struct qcauart));
	struct qcauart *qca;
	const char *mac;
	u32 speed = 115200;
	int ret;

	if (!qcauart_dev)
		return -ENOMEM;

	qcauart_netdev_setup(qcauart_dev);
	SET_NETDEV_DEV(qcauart_dev, &serdev->dev);

	qca = netdev_priv(qcauart_dev);
	if (!qca) {
		pr_err("qca_uart: Fail to retrieve private structure\n");
		ret = -ENOMEM;
		goto free;
	}
	qca->net_dev = qcauart_dev;
	qca->serdev = serdev;
	qcafrm_fsm_init_uart(&qca->frm_handle);

	spin_lock_init(&qca->lock);
	INIT_WORK(&qca->tx_work, qcauart_transmit);

	of_property_read_u32(serdev->dev.of_node, "current-speed", &speed);

	mac = of_get_mac_address(serdev->dev.of_node);

	if (!IS_ERR(mac))
		ether_addr_copy(qca->net_dev->dev_addr, mac);

	if (!is_valid_ether_addr(qca->net_dev->dev_addr)) {
		eth_hw_addr_random(qca->net_dev);
		dev_info(&serdev->dev, "Using random MAC address: %pM\n",
			 qca->net_dev->dev_addr);
	}

	netif_carrier_on(qca->net_dev);
	serdev_device_set_drvdata(serdev, qca);
	serdev_device_set_client_ops(serdev, &qca_serdev_ops);

	ret = serdev_device_open(serdev);
	if (ret) {
		dev_err(&serdev->dev, "Unable to open device %s\n",
			qcauart_dev->name);
		goto free;
	}

	speed = serdev_device_set_baudrate(serdev, speed);
	dev_info(&serdev->dev, "Using baudrate: %u\n", speed);

	serdev_device_set_flow_control(serdev, false);

	ret = register_netdev(qcauart_dev);
	if (ret) {
		dev_err(&serdev->dev, "Unable to register net device %s\n",
			qcauart_dev->name);
		serdev_device_close(serdev);
		cancel_work_sync(&qca->tx_work);
		goto free;
	}

	return 0;

free:
	free_netdev(qcauart_dev);
	return ret;
}