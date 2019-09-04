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
struct drm_vmw_shader_create_arg {int /*<<< orphan*/  shader_handle; int /*<<< orphan*/  offset; int /*<<< orphan*/  size; int /*<<< orphan*/  buffer_handle; int /*<<< orphan*/  shader_type; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int vmw_shader_define (struct drm_device*,struct drm_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int vmw_shader_define_ioctl(struct drm_device *dev, void *data,
			     struct drm_file *file_priv)
{
	struct drm_vmw_shader_create_arg *arg =
		(struct drm_vmw_shader_create_arg *)data;

	return vmw_shader_define(dev, file_priv, arg->shader_type,
				 arg->buffer_handle,
				 arg->size, arg->offset,
				 0, 0,
				 &arg->shader_handle);
}