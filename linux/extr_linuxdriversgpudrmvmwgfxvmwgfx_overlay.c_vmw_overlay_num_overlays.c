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

/* Variables and functions */
 int VMW_MAX_NUM_STREAMS ; 
 int /*<<< orphan*/  vmw_overlay_available (struct vmw_private*) ; 

int vmw_overlay_num_overlays(struct vmw_private *dev_priv)
{
	if (!vmw_overlay_available(dev_priv))
		return 0;

	return VMW_MAX_NUM_STREAMS;
}