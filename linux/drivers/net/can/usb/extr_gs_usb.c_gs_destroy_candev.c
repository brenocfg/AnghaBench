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
struct gs_can {int /*<<< orphan*/  netdev; int /*<<< orphan*/  tx_submitted; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_candev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_candev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gs_destroy_candev(struct gs_can *dev)
{
	unregister_candev(dev->netdev);
	usb_kill_anchored_urbs(&dev->tx_submitted);
	free_candev(dev->netdev);
}