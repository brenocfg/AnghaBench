#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hns3_nic_priv {TYPE_2__* ring_data; int /*<<< orphan*/  dev; struct hnae3_handle* ae_handle; } ;
struct TYPE_3__ {int num_tqps; } ;
struct hnae3_handle {TYPE_1__ kinfo; } ;
struct TYPE_4__ {struct TYPE_4__* ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void hns3_put_ring_config(struct hns3_nic_priv *priv)
{
	struct hnae3_handle *h = priv->ae_handle;
	int i;

	if (!priv->ring_data)
		return;

	for (i = 0; i < h->kinfo.num_tqps; i++) {
		devm_kfree(priv->dev, priv->ring_data[i].ring);
		devm_kfree(priv->dev,
			   priv->ring_data[i + h->kinfo.num_tqps].ring);
	}
	devm_kfree(priv->dev, priv->ring_data);
	priv->ring_data = NULL;
}