#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {TYPE_3__* resource; } ;
struct TYPE_5__ {int /*<<< orphan*/  start; } ;
struct i915_ggtt {int /*<<< orphan*/  mappable_end; TYPE_1__ gmadr; } ;
struct TYPE_8__ {struct pci_dev* pdev; } ;
struct drm_i915_private {struct i915_ggtt ggtt; TYPE_4__ drm; } ;
struct apertures_struct {TYPE_2__* ranges; } ;
struct TYPE_7__ {int flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int IORESOURCE_ROM_SHADOW ; 
 size_t PCI_ROM_RESOURCE ; 
 struct apertures_struct* alloc_apertures (int) ; 
 int drm_fb_helper_remove_conflicting_framebuffers (struct apertures_struct*,char*,int) ; 
 int /*<<< orphan*/  kfree (struct apertures_struct*) ; 

__attribute__((used)) static int i915_kick_out_firmware_fb(struct drm_i915_private *dev_priv)
{
	struct apertures_struct *ap;
	struct pci_dev *pdev = dev_priv->drm.pdev;
	struct i915_ggtt *ggtt = &dev_priv->ggtt;
	bool primary;
	int ret;

	ap = alloc_apertures(1);
	if (!ap)
		return -ENOMEM;

	ap->ranges[0].base = ggtt->gmadr.start;
	ap->ranges[0].size = ggtt->mappable_end;

	primary =
		pdev->resource[PCI_ROM_RESOURCE].flags & IORESOURCE_ROM_SHADOW;

	ret = drm_fb_helper_remove_conflicting_framebuffers(ap, "inteldrmfb", primary);

	kfree(ap);

	return ret;
}