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
typedef  int u8 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int state; } ;
struct mscan_priv {TYPE_1__ can; } ;
typedef  enum can_state { ____Placeholder_can_state } can_state ;

/* Variables and functions */
 int MSCAN_CSCIF ; 
 int /*<<< orphan*/  MSCAN_STATE_RX (int) ; 
 int /*<<< orphan*/  MSCAN_STATE_TX (int) ; 
 size_t max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mscan_priv* netdev_priv (struct net_device*) ; 
 int* state_map ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static enum can_state get_new_state(struct net_device *dev, u8 canrflg)
{
	struct mscan_priv *priv = netdev_priv(dev);

	if (unlikely(canrflg & MSCAN_CSCIF))
		return state_map[max(MSCAN_STATE_RX(canrflg),
				 MSCAN_STATE_TX(canrflg))];

	return priv->can.state;
}