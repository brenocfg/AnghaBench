#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct macsec_secy {scalar_t__ key_len; int /*<<< orphan*/  icv_len; } ;
struct macsec_rx_sc {int /*<<< orphan*/ * sa; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct macsec_rx_sa {int active; struct macsec_rx_sc* sc; TYPE_1__ key; int /*<<< orphan*/  lock; int /*<<< orphan*/  next_pn; } ;
struct genl_info {struct nlattr** attrs; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct macsec_rx_sc*) ; 
 size_t MACSEC_ATTR_IFINDEX ; 
 int /*<<< orphan*/  MACSEC_KEYID_LEN ; 
 int /*<<< orphan*/  MACSEC_RXSC_ATTR_MAX ; 
 size_t MACSEC_SA_ATTR_ACTIVE ; 
 size_t MACSEC_SA_ATTR_AN ; 
 size_t MACSEC_SA_ATTR_KEY ; 
 size_t MACSEC_SA_ATTR_KEYID ; 
 int /*<<< orphan*/  MACSEC_SA_ATTR_MAX ; 
 size_t MACSEC_SA_ATTR_PN ; 
 int PTR_ERR (struct macsec_rx_sc*) ; 
 int /*<<< orphan*/  genl_info_net (struct genl_info*) ; 
 struct macsec_rx_sc* get_rxsc_from_nl (int /*<<< orphan*/ ,struct nlattr**,struct nlattr**,struct net_device**,struct macsec_secy**) ; 
 int init_rx_sa (struct macsec_rx_sa*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct macsec_rx_sa*) ; 
 struct macsec_rx_sa* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 unsigned char nla_get_u8 (struct nlattr*) ; 
 scalar_t__ nla_len (struct nlattr*) ; 
 int /*<<< orphan*/  nla_memcpy (int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_rxsc_config (struct nlattr**,struct nlattr**) ; 
 scalar_t__ parse_sa_config (struct nlattr**,struct nlattr**) ; 
 int /*<<< orphan*/  pr_notice (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct macsec_rx_sa*) ; 
 struct macsec_rx_sa* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  validate_add_rxsa (struct nlattr**) ; 

__attribute__((used)) static int macsec_add_rxsa(struct sk_buff *skb, struct genl_info *info)
{
	struct net_device *dev;
	struct nlattr **attrs = info->attrs;
	struct macsec_secy *secy;
	struct macsec_rx_sc *rx_sc;
	struct macsec_rx_sa *rx_sa;
	unsigned char assoc_num;
	struct nlattr *tb_rxsc[MACSEC_RXSC_ATTR_MAX + 1];
	struct nlattr *tb_sa[MACSEC_SA_ATTR_MAX + 1];
	int err;

	if (!attrs[MACSEC_ATTR_IFINDEX])
		return -EINVAL;

	if (parse_sa_config(attrs, tb_sa))
		return -EINVAL;

	if (parse_rxsc_config(attrs, tb_rxsc))
		return -EINVAL;

	if (!validate_add_rxsa(tb_sa))
		return -EINVAL;

	rtnl_lock();
	rx_sc = get_rxsc_from_nl(genl_info_net(info), attrs, tb_rxsc, &dev, &secy);
	if (IS_ERR(rx_sc)) {
		rtnl_unlock();
		return PTR_ERR(rx_sc);
	}

	assoc_num = nla_get_u8(tb_sa[MACSEC_SA_ATTR_AN]);

	if (nla_len(tb_sa[MACSEC_SA_ATTR_KEY]) != secy->key_len) {
		pr_notice("macsec: nl: add_rxsa: bad key length: %d != %d\n",
			  nla_len(tb_sa[MACSEC_SA_ATTR_KEY]), secy->key_len);
		rtnl_unlock();
		return -EINVAL;
	}

	rx_sa = rtnl_dereference(rx_sc->sa[assoc_num]);
	if (rx_sa) {
		rtnl_unlock();
		return -EBUSY;
	}

	rx_sa = kmalloc(sizeof(*rx_sa), GFP_KERNEL);
	if (!rx_sa) {
		rtnl_unlock();
		return -ENOMEM;
	}

	err = init_rx_sa(rx_sa, nla_data(tb_sa[MACSEC_SA_ATTR_KEY]),
			 secy->key_len, secy->icv_len);
	if (err < 0) {
		kfree(rx_sa);
		rtnl_unlock();
		return err;
	}

	if (tb_sa[MACSEC_SA_ATTR_PN]) {
		spin_lock_bh(&rx_sa->lock);
		rx_sa->next_pn = nla_get_u32(tb_sa[MACSEC_SA_ATTR_PN]);
		spin_unlock_bh(&rx_sa->lock);
	}

	if (tb_sa[MACSEC_SA_ATTR_ACTIVE])
		rx_sa->active = !!nla_get_u8(tb_sa[MACSEC_SA_ATTR_ACTIVE]);

	nla_memcpy(rx_sa->key.id, tb_sa[MACSEC_SA_ATTR_KEYID], MACSEC_KEYID_LEN);
	rx_sa->sc = rx_sc;
	rcu_assign_pointer(rx_sc->sa[assoc_num], rx_sa);

	rtnl_unlock();

	return 0;
}