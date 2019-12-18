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
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {int active; } ;
struct macsec_rx_sc {int active; } ;
struct genl_info {struct nlattr** attrs; } ;
typedef  int /*<<< orphan*/  sci_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct net_device*) ; 
 size_t MACSEC_ATTR_IFINDEX ; 
 size_t MACSEC_RXSC_ATTR_ACTIVE ; 
 int /*<<< orphan*/  MACSEC_RXSC_ATTR_MAX ; 
 size_t MACSEC_RXSC_ATTR_SCI ; 
 int /*<<< orphan*/  MACSEC_UNDEF_SCI ; 
 int PTR_ERR (struct net_device*) ; 
 struct net_device* create_rx_sc (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genl_info_net (struct genl_info*) ; 
 struct net_device* get_dev_from_nl (int /*<<< orphan*/ ,struct nlattr**) ; 
 int /*<<< orphan*/  nla_get_sci (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u8 (struct nlattr*) ; 
 scalar_t__ parse_rxsc_config (struct nlattr**,struct nlattr**) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  validate_add_rxsc (struct nlattr**) ; 

__attribute__((used)) static int macsec_add_rxsc(struct sk_buff *skb, struct genl_info *info)
{
	struct net_device *dev;
	sci_t sci = MACSEC_UNDEF_SCI;
	struct nlattr **attrs = info->attrs;
	struct macsec_rx_sc *rx_sc;
	struct nlattr *tb_rxsc[MACSEC_RXSC_ATTR_MAX + 1];

	if (!attrs[MACSEC_ATTR_IFINDEX])
		return -EINVAL;

	if (parse_rxsc_config(attrs, tb_rxsc))
		return -EINVAL;

	if (!validate_add_rxsc(tb_rxsc))
		return -EINVAL;

	rtnl_lock();
	dev = get_dev_from_nl(genl_info_net(info), attrs);
	if (IS_ERR(dev)) {
		rtnl_unlock();
		return PTR_ERR(dev);
	}

	sci = nla_get_sci(tb_rxsc[MACSEC_RXSC_ATTR_SCI]);

	rx_sc = create_rx_sc(dev, sci);
	if (IS_ERR(rx_sc)) {
		rtnl_unlock();
		return PTR_ERR(rx_sc);
	}

	if (tb_rxsc[MACSEC_RXSC_ATTR_ACTIVE])
		rx_sc->active = !!nla_get_u8(tb_rxsc[MACSEC_RXSC_ATTR_ACTIVE]);

	rtnl_unlock();

	return 0;
}