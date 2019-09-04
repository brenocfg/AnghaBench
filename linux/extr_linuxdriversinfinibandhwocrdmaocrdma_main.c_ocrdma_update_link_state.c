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
typedef  int /*<<< orphan*/  u8 ;
struct ocrdma_dev {int flags; } ;

/* Variables and functions */
 int OCRDMA_FLAGS_LINK_STATUS_INIT ; 
 int /*<<< orphan*/  ocrdma_dispatch_port_active (struct ocrdma_dev*) ; 
 int /*<<< orphan*/  ocrdma_dispatch_port_error (struct ocrdma_dev*) ; 

void ocrdma_update_link_state(struct ocrdma_dev *dev, u8 lstate)
{
	if (!(dev->flags & OCRDMA_FLAGS_LINK_STATUS_INIT)) {
		dev->flags |= OCRDMA_FLAGS_LINK_STATUS_INIT;
		if (!lstate)
			return;
	}

	if (!lstate)
		ocrdma_dispatch_port_error(dev);
	else
		ocrdma_dispatch_port_active(dev);
}