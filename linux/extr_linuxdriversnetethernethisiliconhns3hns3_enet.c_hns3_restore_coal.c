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
typedef  int u16 ;
struct hns3_nic_priv {int vector_num; TYPE_3__* tqp_vector; } ;
struct hns3_enet_coalesce {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  coal; } ;
struct TYPE_4__ {int /*<<< orphan*/  coal; } ;
struct TYPE_6__ {TYPE_2__ rx_group; TYPE_1__ tx_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct hns3_enet_coalesce*,int) ; 

__attribute__((used)) static void hns3_restore_coal(struct hns3_nic_priv *priv,
			      struct hns3_enet_coalesce *tx,
			      struct hns3_enet_coalesce *rx)
{
	u16 vector_num = priv->vector_num;
	int i;

	for (i = 0; i < vector_num; i++) {
		memcpy(&priv->tqp_vector[i].tx_group.coal, tx,
		       sizeof(struct hns3_enet_coalesce));
		memcpy(&priv->tqp_vector[i].rx_group.coal, rx,
		       sizeof(struct hns3_enet_coalesce));
	}
}