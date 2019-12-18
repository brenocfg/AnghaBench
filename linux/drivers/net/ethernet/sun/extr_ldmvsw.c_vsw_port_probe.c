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
typedef  int u64 ;
struct vnet_port {int* raddr; int switch_port; int tso; int vsw; int /*<<< orphan*/  vio; int /*<<< orphan*/  napi; int /*<<< orphan*/  list; int /*<<< orphan*/  clean_timer; scalar_t__ tsolen; struct vnet* dev; struct vnet* vp; } ;
struct vnet {int /*<<< orphan*/  name; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  lock; int /*<<< orphan*/  port_list; } ;
struct vio_device_id {int dummy; } ;
struct vio_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  mp; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  lock; int /*<<< orphan*/  port_list; } ;
struct mdesc_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct vnet*) ; 
 int /*<<< orphan*/  NAPI_POLL_WEIGHT ; 
 int PTR_ERR (struct vnet*) ; 
 int /*<<< orphan*/  VDEV_NETWORK ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct vnet_port*) ; 
 int /*<<< orphan*/  free_netdev (struct vnet*) ; 
 int /*<<< orphan*/  id_prop ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int* mdesc_get_property (struct mdesc_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct mdesc_handle* mdesc_grab () ; 
 int /*<<< orphan*/  mdesc_release (struct mdesc_handle*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_info (struct vnet*,char*,int /*<<< orphan*/ ) ; 
 struct vnet_port* netdev_priv (struct vnet*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct vnet*) ; 
 int /*<<< orphan*/  netif_napi_add (struct vnet*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int*,char*) ; 
 int register_netdev (struct vnet*) ; 
 int /*<<< orphan*/  remote_macaddr_prop ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sunvnet_clean_timer_expire_common ; 
 int /*<<< orphan*/  sunvnet_poll_common ; 
 int /*<<< orphan*/  sunvnet_port_add_txq_common (struct vnet_port*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vio_driver_init (int /*<<< orphan*/ *,struct vio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vio_ldc_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct vnet_port*) ; 
 int /*<<< orphan*/  vio_ldc_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vio_port_up (int /*<<< orphan*/ *) ; 
 struct vnet* vsw_alloc_netdev (int /*<<< orphan*/ ,struct vio_dev*,int,int const) ; 
 struct vnet* vsw_get_vnet (struct mdesc_handle*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  vsw_ldc_cfg ; 
 int /*<<< orphan*/  vsw_port_hwaddr ; 
 int /*<<< orphan*/  vsw_versions ; 
 int /*<<< orphan*/  vsw_vio_ops ; 

__attribute__((used)) static int vsw_port_probe(struct vio_dev *vdev, const struct vio_device_id *id)
{
	struct mdesc_handle *hp;
	struct vnet_port *port;
	unsigned long flags;
	struct vnet *vp;
	struct net_device *dev;
	const u64 *rmac;
	int len, i, err;
	const u64 *port_id;
	u64 handle;

	hp = mdesc_grab();

	rmac = mdesc_get_property(hp, vdev->mp, remote_macaddr_prop, &len);
	err = -ENODEV;
	if (!rmac) {
		pr_err("Port lacks %s property\n", remote_macaddr_prop);
		mdesc_release(hp);
		return err;
	}

	port_id = mdesc_get_property(hp, vdev->mp, id_prop, NULL);
	err = -ENODEV;
	if (!port_id) {
		pr_err("Port lacks %s property\n", id_prop);
		mdesc_release(hp);
		return err;
	}

	/* Get (or create) the vnet associated with this port */
	vp = vsw_get_vnet(hp, vdev->mp, &handle);
	if (IS_ERR(vp)) {
		err = PTR_ERR(vp);
		pr_err("Failed to get vnet for vsw-port\n");
		mdesc_release(hp);
		return err;
	}

	mdesc_release(hp);

	dev = vsw_alloc_netdev(vsw_port_hwaddr, vdev, handle, *port_id);
	if (IS_ERR(dev)) {
		err = PTR_ERR(dev);
		pr_err("Failed to alloc netdev for vsw-port\n");
		return err;
	}

	port = netdev_priv(dev);

	INIT_LIST_HEAD(&port->list);

	for (i = 0; i < ETH_ALEN; i++)
		port->raddr[i] = (*rmac >> (5 - i) * 8) & 0xff;

	port->vp = vp;
	port->dev = dev;
	port->switch_port = 1;
	port->tso = false; /* no tso in vsw, misbehaves in bridge */
	port->tsolen = 0;

	/* Mark the port as belonging to ldmvsw which directs the
	 * the common code to use the net_device in the vnet_port
	 * rather than the net_device in the vnet (which is used
	 * by sunvnet). This bit is used by the VNET_PORT_TO_NET_DEVICE
	 * macro.
	 */
	port->vsw = 1;

	err = vio_driver_init(&port->vio, vdev, VDEV_NETWORK,
			      vsw_versions, ARRAY_SIZE(vsw_versions),
			      &vsw_vio_ops, dev->name);
	if (err)
		goto err_out_free_dev;

	err = vio_ldc_alloc(&port->vio, &vsw_ldc_cfg, port);
	if (err)
		goto err_out_free_dev;

	dev_set_drvdata(&vdev->dev, port);

	netif_napi_add(dev, &port->napi, sunvnet_poll_common,
		       NAPI_POLL_WEIGHT);

	spin_lock_irqsave(&vp->lock, flags);
	list_add_rcu(&port->list, &vp->port_list);
	spin_unlock_irqrestore(&vp->lock, flags);

	timer_setup(&port->clean_timer, sunvnet_clean_timer_expire_common, 0);

	err = register_netdev(dev);
	if (err) {
		pr_err("Cannot register net device, aborting\n");
		goto err_out_del_timer;
	}

	spin_lock_irqsave(&vp->lock, flags);
	sunvnet_port_add_txq_common(port);
	spin_unlock_irqrestore(&vp->lock, flags);

	napi_enable(&port->napi);
	vio_port_up(&port->vio);

	/* assure no carrier until we receive an LDC_EVENT_UP,
	 * even if the vsw config script tries to force us up
	 */
	netif_carrier_off(dev);

	netdev_info(dev, "LDOM vsw-port %pM\n", dev->dev_addr);

	pr_info("%s: PORT ( remote-mac %pM%s )\n", dev->name,
		port->raddr, " switch-port");

	return 0;

err_out_del_timer:
	del_timer_sync(&port->clean_timer);
	list_del_rcu(&port->list);
	synchronize_rcu();
	netif_napi_del(&port->napi);
	dev_set_drvdata(&vdev->dev, NULL);
	vio_ldc_free(&port->vio);

err_out_free_dev:
	free_netdev(dev);
	return err;
}