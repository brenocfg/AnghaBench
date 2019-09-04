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
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_buf_info {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int __drm_legacy_infobufs (struct drm_device*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_one_buf ; 

int drm_legacy_infobufs(struct drm_device *dev, void *data,
			struct drm_file *file_priv)
{
	struct drm_buf_info *request = data;
	return __drm_legacy_infobufs(dev, data, &request->count, copy_one_buf);
}