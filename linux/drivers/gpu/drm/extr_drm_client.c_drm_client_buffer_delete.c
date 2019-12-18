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
struct drm_device {int dummy; } ;
struct drm_client_buffer {TYPE_1__* client; scalar_t__ handle; scalar_t__ gem; int /*<<< orphan*/  vaddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  file; struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_object_put_unlocked (scalar_t__) ; 
 int /*<<< orphan*/  drm_gem_vunmap (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_destroy_dumb (struct drm_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct drm_client_buffer*) ; 

__attribute__((used)) static void drm_client_buffer_delete(struct drm_client_buffer *buffer)
{
	struct drm_device *dev = buffer->client->dev;

	drm_gem_vunmap(buffer->gem, buffer->vaddr);

	if (buffer->gem)
		drm_gem_object_put_unlocked(buffer->gem);

	if (buffer->handle)
		drm_mode_destroy_dumb(dev, buffer->handle, buffer->client->file);

	kfree(buffer);
}