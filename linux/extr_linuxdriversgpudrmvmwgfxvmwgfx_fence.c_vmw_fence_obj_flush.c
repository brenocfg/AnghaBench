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
struct vmw_private {int dummy; } ;
struct vmw_fence_obj {int dummy; } ;
struct TYPE_2__ {struct vmw_private* dev_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVGA_SYNC_GENERIC ; 
 TYPE_1__* fman_from_fence (struct vmw_fence_obj*) ; 
 int /*<<< orphan*/  vmw_fifo_ping_host (struct vmw_private*,int /*<<< orphan*/ ) ; 

void vmw_fence_obj_flush(struct vmw_fence_obj *fence)
{
	struct vmw_private *dev_priv = fman_from_fence(fence)->dev_priv;

	vmw_fifo_ping_host(dev_priv, SVGA_SYNC_GENERIC);
}