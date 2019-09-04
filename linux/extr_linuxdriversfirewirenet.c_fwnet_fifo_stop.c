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
struct fwnet_device {scalar_t__ local_fifo; int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 scalar_t__ FWNET_NO_FIFO_ADDR ; 
 int /*<<< orphan*/  fw_core_remove_address_handler (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fwnet_fifo_stop(struct fwnet_device *dev)
{
	if (dev->local_fifo == FWNET_NO_FIFO_ADDR)
		return;

	fw_core_remove_address_handler(&dev->handler);
	dev->local_fifo = FWNET_NO_FIFO_ADDR;
}