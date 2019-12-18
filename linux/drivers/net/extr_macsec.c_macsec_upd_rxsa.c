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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct macsec_secy {int dummy; } ;
struct macsec_rx_sc {int dummy; } ;
struct macsec_rx_sa {int /*<<< orphan*/  active; int /*<<< orphan*/  lock; int /*<<< orphan*/  next_pn; } ;
struct genl_info {struct nlattr** attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct macsec_rx_sa*) ; 
 size_t MACSEC_ATTR_IFINDEX ; 
 int /*<<< orphan*/  MACSEC_RXSC_ATTR_MAX ; 
 size_t MACSEC_SA_ATTR_ACTIVE ; 
 int /*<<< orphan*/  MACSEC_SA_ATTR_MAX ; 
 size_t MACSEC_SA_ATTR_PN ; 
 int PTR_ERR (struct macsec_rx_sa*) ; 
 int /*<<< orphan*/  genl_info_net (struct genl_info*) ; 
 struct macsec_rx_sa* get_rxsa_from_nl (int /*<<< orphan*/ ,struct nlattr**,struct nlattr**,struct nlattr**,struct net_device**,struct macsec_secy**,struct macsec_rx_sc**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u8 (struct nlattr*) ; 
 scalar_t__ parse_rxsc_config (struct nlattr**,struct nlattr**) ; 
 scalar_t__ parse_sa_config (struct nlattr**,struct nlattr**) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  validate_upd_sa (struct nlattr**) ; 

__attribute__((used)) static int macsec_upd_rxsa(struct sk_buff *skb, struct genl_info *info)
{
	struct nlattr **attrs = info->attrs;
	struct net_device *dev;
	struct macsec_secy *secy;
	struct macsec_rx_sc *rx_sc;
	struct macsec_rx_sa *rx_sa;
	u8 assoc_num;
	struct nlattr *tb_rxsc[MACSEC_RXSC_ATTR_MAX + 1];
	struct nlattr *tb_sa[MACSEC_SA_ATTR_MAX + 1];

	if (!attrs[MACSEC_ATTR_IFINDEX])
		return -EINVAL;

	if (parse_rxsc_config(attrs, tb_rxsc))
		return -EINVAL;

	if (parse_sa_config(attrs, tb_sa))
		return -EINVAL;

	if (!validate_upd_sa(tb_sa))
		return -EINVAL;

	rtnl_lock();
	rx_sa = get_rxsa_from_nl(genl_info_net(info), attrs, tb_rxsc, tb_sa,
				 &dev, &secy, &rx_sc, &assoc_num);
	if (IS_ERR(rx_sa)) {
		rtnl_unlock();
		return PTR_ERR(rx_sa);
	}

	if (tb_sa[MACSEC_SA_ATTR_PN]) {
		spin_lock_bh(&rx_sa->lock);
		rx_sa->next_pn = nla_get_u32(tb_sa[MACSEC_SA_ATTR_PN]);
		spin_unlock_bh(&rx_sa->lock);
	}

	if (tb_sa[MACSEC_SA_ATTR_ACTIVE])
		rx_sa->active = nla_get_u8(tb_sa[MACSEC_SA_ATTR_ACTIVE]);

	rtnl_unlock();
	return 0;
}