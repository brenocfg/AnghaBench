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

/* Variables and functions */
 int /*<<< orphan*/  VIDEO_TYPE ; 
 int sis_drm_alloc (struct drm_device*,struct drm_file*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sis_fb_alloc(struct drm_device *dev, void *data,
			struct drm_file *file_priv)
{
	return sis_drm_alloc(dev, file_priv, data, VIDEO_TYPE);
}