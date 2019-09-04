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
struct drm_psb_private {scalar_t__ vdc_reg; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite16 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void REGISTER_WRITE16(struct drm_device *dev,
					uint32_t reg, uint32_t val)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	iowrite16((val), dev_priv->vdc_reg + (reg));
}