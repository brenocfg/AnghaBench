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
struct vmw_private {int /*<<< orphan*/  fifo; scalar_t__ cman; int /*<<< orphan*/  fman; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmw_cmdbuf_man_destroy (scalar_t__) ; 
 int /*<<< orphan*/  vmw_fence_fifo_down (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_fifo_release (struct vmw_private*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vmw_release_device_late(struct vmw_private *dev_priv)
{
	vmw_fence_fifo_down(dev_priv->fman);
	if (dev_priv->cman)
		vmw_cmdbuf_man_destroy(dev_priv->cman);

	vmw_fifo_release(dev_priv, &dev_priv->fifo);
}