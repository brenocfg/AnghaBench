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
struct drm_mode_cursor2 {scalar_t__ hot_y; scalar_t__ hot_x; } ;
struct drm_mode_cursor {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int drm_mode_cursor_common (struct drm_device*,struct drm_mode_cursor2*,struct drm_file*) ; 
 int /*<<< orphan*/  memcpy (struct drm_mode_cursor2*,struct drm_mode_cursor*,int) ; 

int drm_mode_cursor_ioctl(struct drm_device *dev,
			  void *data, struct drm_file *file_priv)
{
	struct drm_mode_cursor *req = data;
	struct drm_mode_cursor2 new_req;

	memcpy(&new_req, req, sizeof(struct drm_mode_cursor));
	new_req.hot_x = new_req.hot_y = 0;

	return drm_mode_cursor_common(dev, &new_req, file_priv);
}