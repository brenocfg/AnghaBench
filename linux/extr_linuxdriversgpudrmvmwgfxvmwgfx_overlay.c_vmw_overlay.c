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
struct vmw_private {struct vmw_overlay* overlay_priv; } ;
struct vmw_overlay {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 struct vmw_private* vmw_priv (struct drm_device*) ; 

__attribute__((used)) static inline struct vmw_overlay *vmw_overlay(struct drm_device *dev)
{
	struct vmw_private *dev_priv = vmw_priv(dev);
	return dev_priv ? dev_priv->overlay_priv : NULL;
}