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
struct sk_buff {int dummy; } ;
struct mv88e6xxx_ptp_ops {int /*<<< orphan*/  arr1_sts_reg; int /*<<< orphan*/  arr0_sts_reg; } ;
struct mv88e6xxx_port_hwtstamp {int /*<<< orphan*/  rx_queue2; int /*<<< orphan*/  rx_queue; } ;
struct mv88e6xxx_chip {TYPE_2__* info; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {struct mv88e6xxx_ptp_ops* ptp_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  mv88e6xxx_get_rxts (struct mv88e6xxx_chip*,struct mv88e6xxx_port_hwtstamp*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mv88e6xxx_rxtstamp_work(struct mv88e6xxx_chip *chip,
				    struct mv88e6xxx_port_hwtstamp *ps)
{
	const struct mv88e6xxx_ptp_ops *ptp_ops = chip->info->ops->ptp_ops;
	struct sk_buff *skb;

	skb = skb_dequeue(&ps->rx_queue);

	if (skb)
		mv88e6xxx_get_rxts(chip, ps, skb, ptp_ops->arr0_sts_reg,
				   &ps->rx_queue);

	skb = skb_dequeue(&ps->rx_queue2);
	if (skb)
		mv88e6xxx_get_rxts(chip, ps, skb, ptp_ops->arr1_sts_reg,
				   &ps->rx_queue2);
}