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
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  drm_dma_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  __drm_legacy_pci_free (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void drm_pci_free(struct drm_device * dev, drm_dma_handle_t * dmah)
{
	__drm_legacy_pci_free(dev, dmah);
	kfree(dmah);
}