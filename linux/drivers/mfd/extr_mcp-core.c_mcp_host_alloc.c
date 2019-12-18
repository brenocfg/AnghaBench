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
struct TYPE_2__ {int /*<<< orphan*/  release; int /*<<< orphan*/  dma_mask; int /*<<< orphan*/ * bus; struct device* parent; } ;
struct mcp {TYPE_1__ attached_device; int /*<<< orphan*/  lock; } ;
struct device {int /*<<< orphan*/  dma_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 struct mcp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcp_bus_type ; 
 int /*<<< orphan*/  mcp_release ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct mcp *mcp_host_alloc(struct device *parent, size_t size)
{
	struct mcp *mcp;

	mcp = kzalloc(sizeof(struct mcp) + size, GFP_KERNEL);
	if (mcp) {
		spin_lock_init(&mcp->lock);
		device_initialize(&mcp->attached_device);
		mcp->attached_device.parent = parent;
		mcp->attached_device.bus = &mcp_bus_type;
		mcp->attached_device.dma_mask = parent->dma_mask;
		mcp->attached_device.release = mcp_release;
	}
	return mcp;
}