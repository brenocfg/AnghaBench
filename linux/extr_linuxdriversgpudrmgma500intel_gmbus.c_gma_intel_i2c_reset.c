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
struct drm_psb_private {int dummy; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMBUS0 ; 
 int /*<<< orphan*/  GMBUS_REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
gma_intel_i2c_reset(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	GMBUS_REG_WRITE(GMBUS0, 0);
}