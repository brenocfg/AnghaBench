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
struct qxl_device {int /*<<< orphan*/  ddev; } ;
struct drm_qxl_map {int /*<<< orphan*/  offset; int /*<<< orphan*/  handle; } ;
struct drm_file {int dummy; } ;
struct drm_device {struct qxl_device* dev_private; } ;

/* Variables and functions */
 int qxl_mode_dumb_mmap (struct drm_file*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qxl_map_ioctl(struct drm_device *dev, void *data,
			 struct drm_file *file_priv)
{
	struct qxl_device *qdev = dev->dev_private;
	struct drm_qxl_map *qxl_map = data;

	return qxl_mode_dumb_mmap(file_priv, &qdev->ddev, qxl_map->handle,
				  &qxl_map->offset);
}