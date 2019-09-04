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
typedef  int /*<<< orphan*/  u32 ;
struct drm_client_dev {int dummy; } ;
struct drm_client_buffer {int dummy; } ;

/* Variables and functions */
 struct drm_client_buffer* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct drm_client_buffer*) ; 
 int drm_client_buffer_addfb (struct drm_client_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_client_buffer* drm_client_buffer_create (struct drm_client_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_client_buffer_delete (struct drm_client_buffer*) ; 

struct drm_client_buffer *
drm_client_framebuffer_create(struct drm_client_dev *client, u32 width, u32 height, u32 format)
{
	struct drm_client_buffer *buffer;
	int ret;

	buffer = drm_client_buffer_create(client, width, height, format);
	if (IS_ERR(buffer))
		return buffer;

	ret = drm_client_buffer_addfb(buffer, width, height, format);
	if (ret) {
		drm_client_buffer_delete(buffer);
		return ERR_PTR(ret);
	}

	return buffer;
}