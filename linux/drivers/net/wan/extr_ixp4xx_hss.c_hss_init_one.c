#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct port {int /*<<< orphan*/ * npe; int /*<<< orphan*/  napi; int /*<<< orphan*/  plat; TYPE_3__* dev; int /*<<< orphan*/  id; int /*<<< orphan*/  clock_reg; scalar_t__ clock_rate; int /*<<< orphan*/  clock_type; struct net_device* netdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  platform_data; } ;
struct platform_device {TYPE_3__ dev; int /*<<< orphan*/  id; } ;
struct net_device {int tx_queue_len; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  xmit; int /*<<< orphan*/  attach; } ;
typedef  TYPE_1__ hdlc_device ;

/* Variables and functions */
 int /*<<< orphan*/  CLK42X_SPEED_2048KHZ ; 
 int /*<<< orphan*/  CLOCK_EXT ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NAPI_WEIGHT ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,TYPE_3__*) ; 
 struct net_device* alloc_hdlcdev (struct port*) ; 
 TYPE_1__* dev_to_hdlc (struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  hss_hdlc_attach ; 
 int /*<<< orphan*/  hss_hdlc_ops ; 
 int /*<<< orphan*/  hss_hdlc_poll ; 
 int /*<<< orphan*/  hss_hdlc_xmit ; 
 int /*<<< orphan*/  kfree (struct port*) ; 
 struct port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  npe_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * npe_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct port*) ; 
 int register_hdlc_device (struct net_device*) ; 

__attribute__((used)) static int hss_init_one(struct platform_device *pdev)
{
	struct port *port;
	struct net_device *dev;
	hdlc_device *hdlc;
	int err;

	if ((port = kzalloc(sizeof(*port), GFP_KERNEL)) == NULL)
		return -ENOMEM;

	if ((port->npe = npe_request(0)) == NULL) {
		err = -ENODEV;
		goto err_free;
	}

	if ((port->netdev = dev = alloc_hdlcdev(port)) == NULL) {
		err = -ENOMEM;
		goto err_plat;
	}

	SET_NETDEV_DEV(dev, &pdev->dev);
	hdlc = dev_to_hdlc(dev);
	hdlc->attach = hss_hdlc_attach;
	hdlc->xmit = hss_hdlc_xmit;
	dev->netdev_ops = &hss_hdlc_ops;
	dev->tx_queue_len = 100;
	port->clock_type = CLOCK_EXT;
	port->clock_rate = 0;
	port->clock_reg = CLK42X_SPEED_2048KHZ;
	port->id = pdev->id;
	port->dev = &pdev->dev;
	port->plat = pdev->dev.platform_data;
	netif_napi_add(dev, &port->napi, hss_hdlc_poll, NAPI_WEIGHT);

	if ((err = register_hdlc_device(dev)))
		goto err_free_netdev;

	platform_set_drvdata(pdev, port);

	netdev_info(dev, "initialized\n");
	return 0;

err_free_netdev:
	free_netdev(dev);
err_plat:
	npe_release(port->npe);
err_free:
	kfree(port);
	return err;
}