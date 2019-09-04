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
struct fwnet_device {scalar_t__ queued_datagrams; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 scalar_t__ FWNET_MIN_QUEUED_DATAGRAMS ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dec_queued_datagrams(struct fwnet_device *dev)
{
	if (--dev->queued_datagrams == FWNET_MIN_QUEUED_DATAGRAMS)
		netif_wake_queue(dev->netdev);
}