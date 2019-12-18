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
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  port; int /*<<< orphan*/  ca; } ;

/* Variables and functions */
 int EINVAL ; 
 int IFLA_VF_IB_NODE_GUID ; 
 int IFLA_VF_IB_PORT_GUID ; 
 int ib_set_vf_guid (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 

__attribute__((used)) static int ipoib_set_vf_guid(struct net_device *dev, int vf, u64 guid, int type)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);

	if (type != IFLA_VF_IB_NODE_GUID && type != IFLA_VF_IB_PORT_GUID)
		return -EINVAL;

	return ib_set_vf_guid(priv->ca, vf, priv->port, guid, type);
}