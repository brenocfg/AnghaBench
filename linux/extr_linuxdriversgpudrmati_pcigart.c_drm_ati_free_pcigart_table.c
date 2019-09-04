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
struct drm_ati_pcigart_info {int /*<<< orphan*/ * table_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_pci_free (struct drm_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drm_ati_free_pcigart_table(struct drm_device *dev,
				       struct drm_ati_pcigart_info *gart_info)
{
	drm_pci_free(dev, gart_info->table_handle);
	gart_info->table_handle = NULL;
}