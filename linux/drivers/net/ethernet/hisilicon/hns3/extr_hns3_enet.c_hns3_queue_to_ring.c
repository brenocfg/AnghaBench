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
struct hns3_nic_priv {TYPE_1__* ring_data; int /*<<< orphan*/  dev; } ;
struct hnae3_queue {size_t tqp_index; } ;
struct TYPE_2__ {int /*<<< orphan*/  ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNAE3_RING_TYPE_RX ; 
 int /*<<< orphan*/  HNAE3_RING_TYPE_TX ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hns3_ring_get_cfg (struct hnae3_queue*,struct hns3_nic_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns3_queue_to_ring(struct hnae3_queue *tqp,
			      struct hns3_nic_priv *priv)
{
	int ret;

	ret = hns3_ring_get_cfg(tqp, priv, HNAE3_RING_TYPE_TX);
	if (ret)
		return ret;

	ret = hns3_ring_get_cfg(tqp, priv, HNAE3_RING_TYPE_RX);
	if (ret) {
		devm_kfree(priv->dev, priv->ring_data[tqp->tqp_index].ring);
		return ret;
	}

	return 0;
}