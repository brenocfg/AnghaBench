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
struct vmw_private {scalar_t__ cman; } ;

/* Variables and functions */
 int /*<<< orphan*/  might_sleep () ; 
 int vmw_cmdbuf_cur_flush (scalar_t__,int) ; 

int vmw_fifo_flush(struct vmw_private *dev_priv, bool interruptible)
{
	might_sleep();

	if (dev_priv->cman)
		return vmw_cmdbuf_cur_flush(dev_priv->cman, interruptible);
	else
		return 0;
}