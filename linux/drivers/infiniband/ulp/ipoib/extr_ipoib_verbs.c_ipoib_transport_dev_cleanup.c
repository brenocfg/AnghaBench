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
struct ipoib_dev_priv {int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; int /*<<< orphan*/ * qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_destroy_cq (int /*<<< orphan*/ ) ; 
 scalar_t__ ib_destroy_qp (int /*<<< orphan*/ *) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*) ; 

void ipoib_transport_dev_cleanup(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);

	if (priv->qp) {
		if (ib_destroy_qp(priv->qp))
			ipoib_warn(priv, "ib_qp_destroy failed\n");

		priv->qp = NULL;
	}

	ib_destroy_cq(priv->send_cq);
	ib_destroy_cq(priv->recv_cq);
}