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
struct vmw_private {int dummy; } ;
struct vmw_buffer_object {int dummy; } ;

/* Variables and functions */
 int vmw_bo_pin_in_placement (struct vmw_private*,struct vmw_buffer_object*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vmw_vram_placement ; 

int vmw_bo_pin_in_vram(struct vmw_private *dev_priv,
		       struct vmw_buffer_object *buf,
		       bool interruptible)
{
	return vmw_bo_pin_in_placement(dev_priv, buf, &vmw_vram_placement,
				       interruptible);
}