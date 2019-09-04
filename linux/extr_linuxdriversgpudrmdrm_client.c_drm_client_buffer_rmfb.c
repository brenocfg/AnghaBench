#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drm_client_buffer {TYPE_2__* fb; TYPE_3__* client; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {TYPE_4__* dev; int /*<<< orphan*/  file; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int drm_mode_rmfb (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drm_client_buffer_rmfb(struct drm_client_buffer *buffer)
{
	int ret;

	if (!buffer->fb)
		return;

	ret = drm_mode_rmfb(buffer->client->dev, buffer->fb->base.id, buffer->client->file);
	if (ret)
		DRM_DEV_ERROR(buffer->client->dev->dev,
			      "Error removing FB:%u (%d)\n", buffer->fb->base.id, ret);

	buffer->fb = NULL;
}