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
struct drm_ati_pcigart_info {int /*<<< orphan*/ * table_handle; int /*<<< orphan*/  table_size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/ * drm_pci_alloc (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drm_ati_alloc_pcigart_table(struct drm_device *dev,
				       struct drm_ati_pcigart_info *gart_info)
{
	gart_info->table_handle = drm_pci_alloc(dev, gart_info->table_size,
						PAGE_SIZE);
	if (gart_info->table_handle == NULL)
		return -ENOMEM;

	return 0;
}