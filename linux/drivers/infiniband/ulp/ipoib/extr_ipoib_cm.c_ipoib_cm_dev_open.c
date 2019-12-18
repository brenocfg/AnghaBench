#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/ * id; } ;
struct ipoib_dev_priv {TYPE_2__ cm; TYPE_1__* qp; TYPE_3__* ca; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int qp_num; } ;

/* Variables and functions */
 int IPOIB_CM_IETF_ID ; 
 int /*<<< orphan*/  IPOIB_CM_SUPPORTED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 int ib_cm_listen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ib_create_cm_id (TYPE_3__*,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  ib_destroy_cm_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_cm_rx_handler ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,...) ; 

int ipoib_cm_dev_open(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	int ret;

	if (!IPOIB_CM_SUPPORTED(dev->dev_addr))
		return 0;

	priv->cm.id = ib_create_cm_id(priv->ca, ipoib_cm_rx_handler, dev);
	if (IS_ERR(priv->cm.id)) {
		pr_warn("%s: failed to create CM ID\n", priv->ca->name);
		ret = PTR_ERR(priv->cm.id);
		goto err_cm;
	}

	ret = ib_cm_listen(priv->cm.id, cpu_to_be64(IPOIB_CM_IETF_ID | priv->qp->qp_num),
			   0);
	if (ret) {
		pr_warn("%s: failed to listen on ID 0x%llx\n", priv->ca->name,
			IPOIB_CM_IETF_ID | priv->qp->qp_num);
		goto err_listen;
	}

	return 0;

err_listen:
	ib_destroy_cm_id(priv->cm.id);
err_cm:
	priv->cm.id = NULL;
	return ret;
}