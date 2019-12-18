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
struct net_device {int dummy; } ;

/* Variables and functions */
 int C_CAN_MSG_OBJ_RX_FIRST ; 
 int C_CAN_MSG_RX_LOW_LAST ; 
 int /*<<< orphan*/  IF_COMM_CLR_NEWDAT ; 
 int /*<<< orphan*/  c_can_object_get (struct net_device*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void c_can_activate_all_lower_rx_msg_obj(struct net_device *dev,
						       int iface)
{
	int i;

	for (i = C_CAN_MSG_OBJ_RX_FIRST; i <= C_CAN_MSG_RX_LOW_LAST; i++)
		c_can_object_get(dev, iface, i, IF_COMM_CLR_NEWDAT);
}