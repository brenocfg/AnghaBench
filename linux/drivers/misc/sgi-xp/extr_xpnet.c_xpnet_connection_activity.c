#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xpnet_message {int dummy; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 int XPC_NET_CHANNEL ; 
 int /*<<< orphan*/  __clear_bit (short,scalar_t__) ; 
 int /*<<< orphan*/  __set_bit (short,scalar_t__) ; 
 int /*<<< orphan*/  bitmap_empty (unsigned long*,short) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,short) ; 
 int /*<<< orphan*/  netif_carrier_off (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_carrier_on (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
#define  xpConnected 129 
#define  xpMsgReceived 128 
 short xp_max_npartitions ; 
 int /*<<< orphan*/  xpnet ; 
 int /*<<< orphan*/  xpnet_broadcast_lock ; 
 scalar_t__ xpnet_broadcast_partitions ; 
 TYPE_1__* xpnet_device ; 
 int /*<<< orphan*/  xpnet_receive (short,int,struct xpnet_message*) ; 

__attribute__((used)) static void
xpnet_connection_activity(enum xp_retval reason, short partid, int channel,
			  void *data, void *key)
{
	DBUG_ON(partid < 0 || partid >= xp_max_npartitions);
	DBUG_ON(channel != XPC_NET_CHANNEL);

	switch (reason) {
	case xpMsgReceived:	/* message received */
		DBUG_ON(data == NULL);

		xpnet_receive(partid, channel, (struct xpnet_message *)data);
		break;

	case xpConnected:	/* connection completed to a partition */
		spin_lock_bh(&xpnet_broadcast_lock);
		__set_bit(partid, xpnet_broadcast_partitions);
		spin_unlock_bh(&xpnet_broadcast_lock);

		netif_carrier_on(xpnet_device);

		dev_dbg(xpnet, "%s connected to partition %d\n",
			xpnet_device->name, partid);
		break;

	default:
		spin_lock_bh(&xpnet_broadcast_lock);
		__clear_bit(partid, xpnet_broadcast_partitions);
		spin_unlock_bh(&xpnet_broadcast_lock);

		if (bitmap_empty((unsigned long *)xpnet_broadcast_partitions,
				 xp_max_npartitions)) {
			netif_carrier_off(xpnet_device);
		}

		dev_dbg(xpnet, "%s disconnected from partition %d\n",
			xpnet_device->name, partid);
		break;
	}
}