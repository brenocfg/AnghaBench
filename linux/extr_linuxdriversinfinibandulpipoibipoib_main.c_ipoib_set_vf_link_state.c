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
struct net_device {int dummy; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  port; int /*<<< orphan*/  ca; } ;

/* Variables and functions */
 int ib_set_vf_link_state (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 

__attribute__((used)) static int ipoib_set_vf_link_state(struct net_device *dev, int vf, int link_state)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);

	return ib_set_vf_link_state(priv->ca, vf, priv->port, link_state);
}