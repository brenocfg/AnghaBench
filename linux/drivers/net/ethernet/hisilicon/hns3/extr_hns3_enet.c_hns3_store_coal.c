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
struct hns3_nic_priv {TYPE_3__* tqp_vector; int /*<<< orphan*/  rx_coal; int /*<<< orphan*/  tx_coal; } ;
struct hns3_enet_coalesce {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  coal; } ;
struct TYPE_4__ {int /*<<< orphan*/  coal; } ;
struct TYPE_6__ {TYPE_2__ rx_group; TYPE_1__ tx_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void hns3_store_coal(struct hns3_nic_priv *priv)
{
	/* ethtool only support setting and querying one coal
	 * configuration for now, so save the vector 0' coal
	 * configuration here in order to restore it.
	 */
	memcpy(&priv->tx_coal, &priv->tqp_vector[0].tx_group.coal,
	       sizeof(struct hns3_enet_coalesce));
	memcpy(&priv->rx_coal, &priv->tqp_vector[0].rx_group.coal,
	       sizeof(struct hns3_enet_coalesce));
}