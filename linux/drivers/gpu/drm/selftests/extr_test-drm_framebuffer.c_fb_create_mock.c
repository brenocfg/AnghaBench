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
struct drm_mode_fb_cmd2 {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct drm_framebuffer* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_framebuffer *fb_create_mock(struct drm_device *dev,
					      struct drm_file *file_priv,
					      const struct drm_mode_fb_cmd2 *mode_cmd)
{
	int *buffer_created = dev->dev_private;
	*buffer_created = 1;
	return ERR_PTR(-EINVAL);
}