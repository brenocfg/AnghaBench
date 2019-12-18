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
struct hns3_nic_priv {int vector_num; int /*<<< orphan*/  rx_coal; TYPE_3__* tqp_vector; int /*<<< orphan*/  tx_coal; } ;
struct hns3_enet_coalesce {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  coal; } ;
struct TYPE_5__ {int /*<<< orphan*/  coal; } ;
struct TYPE_6__ {TYPE_1__ rx_group; TYPE_2__ tx_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void hns3_restore_coal(struct hns3_nic_priv *priv)
{
	u16 vector_num = priv->vector_num;
	int i;

	for (i = 0; i < vector_num; i++) {
		memcpy(&priv->tqp_vector[i].tx_group.coal, &priv->tx_coal,
		       sizeof(struct hns3_enet_coalesce));
		memcpy(&priv->tqp_vector[i].rx_group.coal, &priv->rx_coal,
		       sizeof(struct hns3_enet_coalesce));
	}
}