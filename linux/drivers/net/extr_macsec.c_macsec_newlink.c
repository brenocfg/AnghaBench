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
typedef  scalar_t__ u8 ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int /*<<< orphan*/  rx_handler; scalar_t__ mtu; int /*<<< orphan*/  priv_flags; } ;
struct net {int dummy; } ;
struct macsec_dev {struct net_device* real_dev; } ;
typedef  int /*<<< orphan*/  sci_t ;
typedef  int /*<<< orphan*/  rx_handler_func_t ;

/* Variables and functions */
 scalar_t__ DEFAULT_ICV_LEN ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  IFF_MACSEC ; 
 size_t IFLA_LINK ; 
 size_t IFLA_MACSEC_ICV_LEN ; 
 size_t IFLA_MACSEC_PORT ; 
 size_t IFLA_MACSEC_SCI ; 
 int /*<<< orphan*/  MACSEC_PORT_ES ; 
 struct net_device* __dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_to_sci (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkwatch_fire_event (struct net_device*) ; 
 int macsec_add_dev (struct net_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int macsec_changelink_common (struct net_device*,struct nlattr**) ; 
 int /*<<< orphan*/  macsec_del_dev (struct macsec_dev*) ; 
 scalar_t__ macsec_extra_len (int) ; 
 int /*<<< orphan*/  macsec_generation ; 
 int /*<<< orphan*/ * macsec_handle_frame ; 
 struct macsec_dev* macsec_priv (struct net_device*) ; 
 int netdev_upper_dev_link (struct net_device*,struct net_device*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  netdev_upper_dev_unlink (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  netif_stacked_transfer_operstate (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  nla_get_be16 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_sci (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 scalar_t__ nla_get_u8 (struct nlattr*) ; 
 int register_macsec_dev (struct net_device*,struct net_device*) ; 
 int register_netdevice (struct net_device*) ; 
 int /*<<< orphan*/ * rtnl_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ sci_exists (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 

__attribute__((used)) static int macsec_newlink(struct net *net, struct net_device *dev,
			  struct nlattr *tb[], struct nlattr *data[],
			  struct netlink_ext_ack *extack)
{
	struct macsec_dev *macsec = macsec_priv(dev);
	struct net_device *real_dev;
	int err;
	sci_t sci;
	u8 icv_len = DEFAULT_ICV_LEN;
	rx_handler_func_t *rx_handler;

	if (!tb[IFLA_LINK])
		return -EINVAL;
	real_dev = __dev_get_by_index(net, nla_get_u32(tb[IFLA_LINK]));
	if (!real_dev)
		return -ENODEV;

	dev->priv_flags |= IFF_MACSEC;

	macsec->real_dev = real_dev;

	if (data && data[IFLA_MACSEC_ICV_LEN])
		icv_len = nla_get_u8(data[IFLA_MACSEC_ICV_LEN]);
	dev->mtu = real_dev->mtu - icv_len - macsec_extra_len(true);

	rx_handler = rtnl_dereference(real_dev->rx_handler);
	if (rx_handler && rx_handler != macsec_handle_frame)
		return -EBUSY;

	err = register_netdevice(dev);
	if (err < 0)
		return err;

	err = netdev_upper_dev_link(real_dev, dev, extack);
	if (err < 0)
		goto unregister;

	/* need to be already registered so that ->init has run and
	 * the MAC addr is set
	 */
	if (data && data[IFLA_MACSEC_SCI])
		sci = nla_get_sci(data[IFLA_MACSEC_SCI]);
	else if (data && data[IFLA_MACSEC_PORT])
		sci = dev_to_sci(dev, nla_get_be16(data[IFLA_MACSEC_PORT]));
	else
		sci = dev_to_sci(dev, MACSEC_PORT_ES);

	if (rx_handler && sci_exists(real_dev, sci)) {
		err = -EBUSY;
		goto unlink;
	}

	err = macsec_add_dev(dev, sci, icv_len);
	if (err)
		goto unlink;

	if (data) {
		err = macsec_changelink_common(dev, data);
		if (err)
			goto del_dev;
	}

	err = register_macsec_dev(real_dev, dev);
	if (err < 0)
		goto del_dev;

	netif_stacked_transfer_operstate(real_dev, dev);
	linkwatch_fire_event(dev);

	macsec_generation++;

	return 0;

del_dev:
	macsec_del_dev(macsec);
unlink:
	netdev_upper_dev_unlink(real_dev, dev);
unregister:
	unregister_netdevice(dev);
	return err;
}