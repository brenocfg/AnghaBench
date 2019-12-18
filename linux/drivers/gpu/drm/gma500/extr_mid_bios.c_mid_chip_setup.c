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
 int /*<<< orphan*/  mid_get_fuse_settings (struct drm_device*) ; 
 int /*<<< orphan*/  mid_get_pci_revID (struct drm_psb_private*) ; 
 int /*<<< orphan*/  mid_get_vbt_data (struct drm_psb_private*) ; 

int mid_chip_setup(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	mid_get_fuse_settings(dev);
	mid_get_vbt_data(dev_priv);
	mid_get_pci_revID(dev_priv);
	return 0;
}