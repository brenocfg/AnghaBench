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
typedef  size_t u8 ;
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct macsec_secy {int dummy; } ;
struct macsec_rx_sc {int /*<<< orphan*/ * sa; } ;
struct macsec_rx_sa {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 struct macsec_rx_sa* ERR_CAST (struct macsec_rx_sc*) ; 
 struct macsec_rx_sa* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct macsec_rx_sc*) ; 
 size_t MACSEC_NUM_AN ; 
 size_t MACSEC_SA_ATTR_AN ; 
 struct macsec_rx_sc* get_rxsc_from_nl (struct net*,struct nlattr**,struct nlattr**,struct net_device**,struct macsec_secy**) ; 
 size_t nla_get_u8 (struct nlattr*) ; 
 struct macsec_rx_sa* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct macsec_rx_sa *get_rxsa_from_nl(struct net *net,
					     struct nlattr **attrs,
					     struct nlattr **tb_rxsc,
					     struct nlattr **tb_sa,
					     struct net_device **devp,
					     struct macsec_secy **secyp,
					     struct macsec_rx_sc **scp,
					     u8 *assoc_num)
{
	struct macsec_rx_sc *rx_sc;
	struct macsec_rx_sa *rx_sa;

	if (!tb_sa[MACSEC_SA_ATTR_AN])
		return ERR_PTR(-EINVAL);

	*assoc_num = nla_get_u8(tb_sa[MACSEC_SA_ATTR_AN]);
	if (*assoc_num >= MACSEC_NUM_AN)
		return ERR_PTR(-EINVAL);

	rx_sc = get_rxsc_from_nl(net, attrs, tb_rxsc, devp, secyp);
	if (IS_ERR(rx_sc))
		return ERR_CAST(rx_sc);

	rx_sa = rtnl_dereference(rx_sc->sa[*assoc_num]);
	if (!rx_sa)
		return ERR_PTR(-ENODEV);

	*scp = rx_sc;
	return rx_sa;
}