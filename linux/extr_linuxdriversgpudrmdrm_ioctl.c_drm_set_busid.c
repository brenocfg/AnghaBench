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
struct drm_master {int /*<<< orphan*/  unique_len; int /*<<< orphan*/ * unique; } ;
struct drm_file {struct drm_master* master; } ;
struct drm_device {int /*<<< orphan*/  unique; scalar_t__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ dev_is_pci (scalar_t__) ; 
 int drm_pci_set_busid (struct drm_device*,struct drm_master*) ; 
 int /*<<< orphan*/  drm_unset_busid (struct drm_device*,struct drm_master*) ; 
 int /*<<< orphan*/ * kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drm_set_busid(struct drm_device *dev, struct drm_file *file_priv)
{
	struct drm_master *master = file_priv->master;
	int ret;

	if (master->unique != NULL)
		drm_unset_busid(dev, master);

	if (dev->dev && dev_is_pci(dev->dev)) {
		ret = drm_pci_set_busid(dev, master);
		if (ret) {
			drm_unset_busid(dev, master);
			return ret;
		}
	} else {
		WARN_ON(!dev->unique);
		master->unique = kstrdup(dev->unique, GFP_KERNEL);
		if (master->unique)
			master->unique_len = strlen(dev->unique);
	}

	return 0;
}