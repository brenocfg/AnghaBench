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
struct drm_device {struct bochs_device* dev_private; } ;
struct bochs_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bochs_hw_fini (struct drm_device*) ; 
 int /*<<< orphan*/  bochs_kms_fini (struct bochs_device*) ; 
 int /*<<< orphan*/  bochs_mm_fini (struct bochs_device*) ; 
 int /*<<< orphan*/  kfree (struct bochs_device*) ; 

__attribute__((used)) static void bochs_unload(struct drm_device *dev)
{
	struct bochs_device *bochs = dev->dev_private;

	bochs_kms_fini(bochs);
	bochs_mm_fini(bochs);
	bochs_hw_fini(dev);
	kfree(bochs);
	dev->dev_private = NULL;
}