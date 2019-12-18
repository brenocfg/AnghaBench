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
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  port; int /*<<< orphan*/  ca; } ;
struct ifla_vf_info {int vf; int /*<<< orphan*/  mac; } ;

/* Variables and functions */
 int ib_get_vf_config (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct ifla_vf_info*) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipoib_get_vf_config(struct net_device *dev, int vf,
			       struct ifla_vf_info *ivf)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	int err;

	err = ib_get_vf_config(priv->ca, vf, priv->port, ivf);
	if (err)
		return err;

	ivf->vf = vf;
	memcpy(ivf->mac, dev->dev_addr, dev->addr_len);

	return 0;
}