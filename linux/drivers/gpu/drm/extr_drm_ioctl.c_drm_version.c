#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_version {int /*<<< orphan*/  desc_len; int /*<<< orphan*/  desc; int /*<<< orphan*/  date_len; int /*<<< orphan*/  date; int /*<<< orphan*/  name_len; int /*<<< orphan*/  name; int /*<<< orphan*/  version_patchlevel; int /*<<< orphan*/  version_minor; int /*<<< orphan*/  version_major; } ;
struct drm_file {int dummy; } ;
struct drm_device {TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  desc; int /*<<< orphan*/  date; int /*<<< orphan*/  name; int /*<<< orphan*/  patchlevel; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;

/* Variables and functions */
 int drm_copy_field (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int drm_version(struct drm_device *dev, void *data,
		       struct drm_file *file_priv)
{
	struct drm_version *version = data;
	int err;

	version->version_major = dev->driver->major;
	version->version_minor = dev->driver->minor;
	version->version_patchlevel = dev->driver->patchlevel;
	err = drm_copy_field(version->name, &version->name_len,
			dev->driver->name);
	if (!err)
		err = drm_copy_field(version->date, &version->date_len,
				dev->driver->date);
	if (!err)
		err = drm_copy_field(version->desc, &version->desc_len,
				dev->driver->desc);

	return err;
}