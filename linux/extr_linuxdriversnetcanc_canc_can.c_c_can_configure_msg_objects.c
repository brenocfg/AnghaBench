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
 int C_CAN_MSG_OBJ_RX_LAST ; 
 int C_CAN_NO_OF_OBJECTS ; 
 int /*<<< orphan*/  IF_MCONT_RCV ; 
 int /*<<< orphan*/  IF_MCONT_RCV_EOB ; 
 int /*<<< orphan*/  IF_RX ; 
 int /*<<< orphan*/  c_can_inval_msg_object (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  c_can_setup_receive_object (struct net_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void c_can_configure_msg_objects(struct net_device *dev)
{
	int i;

	/* first invalidate all message objects */
	for (i = C_CAN_MSG_OBJ_RX_FIRST; i <= C_CAN_NO_OF_OBJECTS; i++)
		c_can_inval_msg_object(dev, IF_RX, i);

	/* setup receive message objects */
	for (i = C_CAN_MSG_OBJ_RX_FIRST; i < C_CAN_MSG_OBJ_RX_LAST; i++)
		c_can_setup_receive_object(dev, IF_RX, i, 0, 0, IF_MCONT_RCV);

	c_can_setup_receive_object(dev, IF_RX, C_CAN_MSG_OBJ_RX_LAST, 0, 0,
				   IF_MCONT_RCV_EOB);
}