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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct c_can_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON_MSG (int,char*) ; 
 int /*<<< orphan*/  CAN_LED_EVENT_RX ; 
 int C_CAN_MSG_OBJ_RX_LAST ; 
 int c_can_adjust_pending (int) ; 
 int c_can_get_pending (struct c_can_priv*) ; 
 int c_can_read_objects (struct net_device*,struct c_can_priv*,int,int) ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 struct c_can_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int c_can_do_rx_poll(struct net_device *dev, int quota)
{
	struct c_can_priv *priv = netdev_priv(dev);
	u32 pkts = 0, pend = 0, toread, n;

	/*
	 * It is faster to read only one 16bit register. This is only possible
	 * for a maximum number of 16 objects.
	 */
	BUILD_BUG_ON_MSG(C_CAN_MSG_OBJ_RX_LAST > 16,
			"Implementation does not support more message objects than 16");

	while (quota > 0) {
		if (!pend) {
			pend = c_can_get_pending(priv);
			if (!pend)
				break;
			/*
			 * If the pending field has a gap, handle the
			 * bits above the gap first.
			 */
			toread = c_can_adjust_pending(pend);
		} else {
			toread = pend;
		}
		/* Remove the bits from pend */
		pend &= ~toread;
		/* Read the objects */
		n = c_can_read_objects(dev, priv, toread, quota);
		pkts += n;
		quota -= n;
	}

	if (pkts)
		can_led_event(dev, CAN_LED_EVENT_RX);

	return pkts;
}