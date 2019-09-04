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
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ drm_buf_info32_t ;

/* Variables and functions */
 int __drm_legacy_infobufs (struct drm_device*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_one_buf32 ; 

__attribute__((used)) static int drm_legacy_infobufs32(struct drm_device *dev, void *data,
			struct drm_file *file_priv)
{
	drm_buf_info32_t *request = data;
	return __drm_legacy_infobufs(dev, data, &request->count, copy_one_buf32);
}