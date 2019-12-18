#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hns3_nic_priv {TYPE_2__* ring_data; int /*<<< orphan*/ * dev; struct hnae3_handle* ae_handle; } ;
struct TYPE_4__ {int num_tqps; int /*<<< orphan*/ * tqp; } ;
struct hnae3_handle {TYPE_1__ kinfo; struct pci_dev* pdev; } ;
struct TYPE_5__ {struct TYPE_5__* ring; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  array3_size (int,int,int) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* devm_kzalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hns3_queue_to_ring (int /*<<< orphan*/ ,struct hns3_nic_priv*) ; 

__attribute__((used)) static int hns3_get_ring_config(struct hns3_nic_priv *priv)
{
	struct hnae3_handle *h = priv->ae_handle;
	struct pci_dev *pdev = h->pdev;
	int i, ret;

	priv->ring_data =  devm_kzalloc(&pdev->dev,
					array3_size(h->kinfo.num_tqps,
						    sizeof(*priv->ring_data),
						    2),
					GFP_KERNEL);
	if (!priv->ring_data)
		return -ENOMEM;

	for (i = 0; i < h->kinfo.num_tqps; i++) {
		ret = hns3_queue_to_ring(h->kinfo.tqp[i], priv);
		if (ret)
			goto err;
	}

	return 0;
err:
	while (i--) {
		devm_kfree(priv->dev, priv->ring_data[i].ring);
		devm_kfree(priv->dev,
			   priv->ring_data[i + h->kinfo.num_tqps].ring);
	}

	devm_kfree(&pdev->dev, priv->ring_data);
	priv->ring_data = NULL;
	return ret;
}