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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct rsi_hw {TYPE_1__* host_intf_ops; } ;
struct rsi_common {int coex_mode; int /*<<< orphan*/  tx_bus_mutex; struct rsi_hw* priv; } ;
struct TYPE_2__ {int (* write_pkt ) (struct rsi_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct rsi_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rsi_send_pkt_to_bus(struct rsi_common *common, struct sk_buff *skb)
{
	struct rsi_hw *adapter = common->priv;
	int status;

	if (common->coex_mode > 1)
		mutex_lock(&common->tx_bus_mutex);

	status = adapter->host_intf_ops->write_pkt(common->priv,
						   skb->data, skb->len);

	if (common->coex_mode > 1)
		mutex_unlock(&common->tx_bus_mutex);

	return status;
}