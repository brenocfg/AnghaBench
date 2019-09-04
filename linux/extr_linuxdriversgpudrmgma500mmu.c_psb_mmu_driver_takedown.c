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
struct psb_mmu_driver {int /*<<< orphan*/  default_pd; int /*<<< orphan*/  bif_ctrl; struct drm_device* dev; } ;
struct drm_psb_private {int dummy; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSB_CR_BIF_CTRL ; 
 int /*<<< orphan*/  PSB_WSGX32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct psb_mmu_driver*) ; 
 int /*<<< orphan*/  psb_mmu_free_pagedir (int /*<<< orphan*/ ) ; 

void psb_mmu_driver_takedown(struct psb_mmu_driver *driver)
{
	struct drm_device *dev = driver->dev;
	struct drm_psb_private *dev_priv = dev->dev_private;

	PSB_WSGX32(driver->bif_ctrl, PSB_CR_BIF_CTRL);
	psb_mmu_free_pagedir(driver->default_pd);
	kfree(driver);
}