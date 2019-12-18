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
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct nsim_trap_item {scalar_t__ action; int /*<<< orphan*/  trap_ctx; } ;
struct nsim_trap_data {int /*<<< orphan*/  trap_lock; struct nsim_trap_item* trap_items_arr; } ;
struct nsim_dev_port {int /*<<< orphan*/  devlink_port; TYPE_1__* ns; } ;
struct nsim_dev {struct nsim_trap_data* trap_data; } ;
struct devlink {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  netdev; struct nsim_dev* nsim_dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ DEVLINK_TRAP_ACTION_DROP ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  devlink_trap_report (struct devlink*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 struct sk_buff* nsim_dev_trap_skb_build () ; 
 int /*<<< orphan*/  nsim_traps_arr ; 
 struct devlink* priv_to_devlink (struct nsim_dev*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nsim_dev_trap_report(struct nsim_dev_port *nsim_dev_port)
{
	struct nsim_dev *nsim_dev = nsim_dev_port->ns->nsim_dev;
	struct devlink *devlink = priv_to_devlink(nsim_dev);
	struct nsim_trap_data *nsim_trap_data;
	int i;

	nsim_trap_data = nsim_dev->trap_data;

	spin_lock(&nsim_trap_data->trap_lock);
	for (i = 0; i < ARRAY_SIZE(nsim_traps_arr); i++) {
		struct nsim_trap_item *nsim_trap_item;
		struct sk_buff *skb;

		nsim_trap_item = &nsim_trap_data->trap_items_arr[i];
		if (nsim_trap_item->action == DEVLINK_TRAP_ACTION_DROP)
			continue;

		skb = nsim_dev_trap_skb_build();
		if (!skb)
			continue;
		skb->dev = nsim_dev_port->ns->netdev;

		/* Trapped packets are usually passed to devlink in softIRQ,
		 * but in this case they are generated in a workqueue. Disable
		 * softIRQs to prevent lockdep from complaining about
		 * "incosistent lock state".
		 */
		local_bh_disable();
		devlink_trap_report(devlink, skb, nsim_trap_item->trap_ctx,
				    &nsim_dev_port->devlink_port);
		local_bh_enable();
		consume_skb(skb);
	}
	spin_unlock(&nsim_trap_data->trap_lock);
}