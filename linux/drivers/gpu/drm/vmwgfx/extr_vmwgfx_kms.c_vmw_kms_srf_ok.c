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
typedef  scalar_t__ uint32_t ;
struct vmw_private {scalar_t__ texture_max_width; scalar_t__ texture_max_height; } ;

/* Variables and functions */

__attribute__((used)) static bool
vmw_kms_srf_ok(struct vmw_private *dev_priv, uint32_t width, uint32_t height)
{
	if (width  > dev_priv->texture_max_width ||
	    height > dev_priv->texture_max_height)
		return false;

	return true;
}