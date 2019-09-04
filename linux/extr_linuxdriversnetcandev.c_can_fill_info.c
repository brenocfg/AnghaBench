#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct can_ctrlmode {scalar_t__ bitrate; int /*<<< orphan*/  flags; } ;
struct can_priv {int state; int restart_ms; int termination_const_cnt; int bitrate_const_cnt; int data_bitrate_const_cnt; struct can_ctrlmode bitrate_max; struct can_ctrlmode* data_bitrate_const; struct can_ctrlmode* bitrate_const; struct can_ctrlmode* termination_const; int /*<<< orphan*/  termination; struct can_ctrlmode* data_bittiming_const; struct can_ctrlmode data_bittiming; int /*<<< orphan*/  (* do_get_berr_counter ) (struct net_device const*,struct can_ctrlmode*) ;struct can_ctrlmode clock; struct can_ctrlmode* bittiming_const; struct can_ctrlmode bittiming; int /*<<< orphan*/  (* do_get_state ) (struct net_device const*,int*) ;int /*<<< orphan*/  ctrlmode; } ;
struct can_berr_counter {scalar_t__ bitrate; int /*<<< orphan*/  flags; } ;
typedef  enum can_state { ____Placeholder_can_state } can_state ;
typedef  int /*<<< orphan*/  cm ;
typedef  int /*<<< orphan*/  bec ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  IFLA_CAN_BERR_COUNTER ; 
 int /*<<< orphan*/  IFLA_CAN_BITRATE_CONST ; 
 int /*<<< orphan*/  IFLA_CAN_BITRATE_MAX ; 
 int /*<<< orphan*/  IFLA_CAN_BITTIMING ; 
 int /*<<< orphan*/  IFLA_CAN_BITTIMING_CONST ; 
 int /*<<< orphan*/  IFLA_CAN_CLOCK ; 
 int /*<<< orphan*/  IFLA_CAN_CTRLMODE ; 
 int /*<<< orphan*/  IFLA_CAN_DATA_BITRATE_CONST ; 
 int /*<<< orphan*/  IFLA_CAN_DATA_BITTIMING ; 
 int /*<<< orphan*/  IFLA_CAN_DATA_BITTIMING_CONST ; 
 int /*<<< orphan*/  IFLA_CAN_RESTART_MS ; 
 int /*<<< orphan*/  IFLA_CAN_STATE ; 
 int /*<<< orphan*/  IFLA_CAN_TERMINATION ; 
 int /*<<< orphan*/  IFLA_CAN_TERMINATION_CONST ; 
 struct can_priv* netdev_priv (struct net_device const*) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct can_ctrlmode*) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct net_device const*,int*) ; 
 int /*<<< orphan*/  stub2 (struct net_device const*,struct can_ctrlmode*) ; 

__attribute__((used)) static int can_fill_info(struct sk_buff *skb, const struct net_device *dev)
{
	struct can_priv *priv = netdev_priv(dev);
	struct can_ctrlmode cm = {.flags = priv->ctrlmode};
	struct can_berr_counter bec;
	enum can_state state = priv->state;

	if (priv->do_get_state)
		priv->do_get_state(dev, &state);

	if ((priv->bittiming.bitrate &&
	     nla_put(skb, IFLA_CAN_BITTIMING,
		     sizeof(priv->bittiming), &priv->bittiming)) ||

	    (priv->bittiming_const &&
	     nla_put(skb, IFLA_CAN_BITTIMING_CONST,
		     sizeof(*priv->bittiming_const), priv->bittiming_const)) ||

	    nla_put(skb, IFLA_CAN_CLOCK, sizeof(priv->clock), &priv->clock) ||
	    nla_put_u32(skb, IFLA_CAN_STATE, state) ||
	    nla_put(skb, IFLA_CAN_CTRLMODE, sizeof(cm), &cm) ||
	    nla_put_u32(skb, IFLA_CAN_RESTART_MS, priv->restart_ms) ||

	    (priv->do_get_berr_counter &&
	     !priv->do_get_berr_counter(dev, &bec) &&
	     nla_put(skb, IFLA_CAN_BERR_COUNTER, sizeof(bec), &bec)) ||

	    (priv->data_bittiming.bitrate &&
	     nla_put(skb, IFLA_CAN_DATA_BITTIMING,
		     sizeof(priv->data_bittiming), &priv->data_bittiming)) ||

	    (priv->data_bittiming_const &&
	     nla_put(skb, IFLA_CAN_DATA_BITTIMING_CONST,
		     sizeof(*priv->data_bittiming_const),
		     priv->data_bittiming_const)) ||

	    (priv->termination_const &&
	     (nla_put_u16(skb, IFLA_CAN_TERMINATION, priv->termination) ||
	      nla_put(skb, IFLA_CAN_TERMINATION_CONST,
		      sizeof(*priv->termination_const) *
		      priv->termination_const_cnt,
		      priv->termination_const))) ||

	    (priv->bitrate_const &&
	     nla_put(skb, IFLA_CAN_BITRATE_CONST,
		     sizeof(*priv->bitrate_const) *
		     priv->bitrate_const_cnt,
		     priv->bitrate_const)) ||

	    (priv->data_bitrate_const &&
	     nla_put(skb, IFLA_CAN_DATA_BITRATE_CONST,
		     sizeof(*priv->data_bitrate_const) *
		     priv->data_bitrate_const_cnt,
		     priv->data_bitrate_const)) ||

	    (nla_put(skb, IFLA_CAN_BITRATE_MAX,
		     sizeof(priv->bitrate_max),
		     &priv->bitrate_max))
	    )

		return -EMSGSIZE;

	return 0;
}