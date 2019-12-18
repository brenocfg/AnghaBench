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
struct kvaser_usb {int nchannels; TYPE_1__** nets; } ;
struct TYPE_2__ {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_candev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvaser_usb_unlink_all_urbs (struct kvaser_usb*) ; 
 int /*<<< orphan*/  unregister_candev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvaser_usb_remove_interfaces(struct kvaser_usb *dev)
{
	int i;

	for (i = 0; i < dev->nchannels; i++) {
		if (!dev->nets[i])
			continue;

		unregister_candev(dev->nets[i]->netdev);
	}

	kvaser_usb_unlink_all_urbs(dev);

	for (i = 0; i < dev->nchannels; i++) {
		if (!dev->nets[i])
			continue;

		free_candev(dev->nets[i]->netdev);
	}
}