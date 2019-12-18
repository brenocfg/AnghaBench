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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct peak_usb_device {int /*<<< orphan*/  netdev; TYPE_1__ can; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_STATE_ERROR_ACTIVE ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 

void peak_usb_restart_complete(struct peak_usb_device *dev)
{
	/* finally MUST update can state */
	dev->can.state = CAN_STATE_ERROR_ACTIVE;

	/* netdev queue can be awaken now */
	netif_wake_queue(dev->netdev);
}