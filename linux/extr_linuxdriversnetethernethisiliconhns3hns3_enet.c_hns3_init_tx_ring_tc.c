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
struct hns3_nic_priv {TYPE_2__* ring_data; TYPE_3__* ae_handle; } ;
struct hnae3_tc_info {int tqp_count; int tqp_offset; int /*<<< orphan*/  tc; int /*<<< orphan*/  enable; } ;
struct hnae3_queue {int dummy; } ;
struct hnae3_knic_private_info {struct hnae3_tc_info* tc_info; } ;
struct TYPE_6__ {struct hnae3_knic_private_info kinfo; } ;
struct TYPE_5__ {TYPE_1__* ring; } ;
struct TYPE_4__ {struct hnae3_queue* tqp; } ;

/* Variables and functions */
 int HNAE3_MAX_TC ; 
 int /*<<< orphan*/  HNS3_RING_TX_RING_TC_REG ; 
 int /*<<< orphan*/  hns3_write_dev (struct hnae3_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns3_init_tx_ring_tc(struct hns3_nic_priv *priv)
{
	struct hnae3_knic_private_info *kinfo = &priv->ae_handle->kinfo;
	int i;

	for (i = 0; i < HNAE3_MAX_TC; i++) {
		struct hnae3_tc_info *tc_info = &kinfo->tc_info[i];
		int j;

		if (!tc_info->enable)
			continue;

		for (j = 0; j < tc_info->tqp_count; j++) {
			struct hnae3_queue *q;

			q = priv->ring_data[tc_info->tqp_offset + j].ring->tqp;
			hns3_write_dev(q, HNS3_RING_TX_RING_TC_REG,
				       tc_info->tc);
		}
	}
}