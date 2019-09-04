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
struct drm_client_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_client_buffer_delete (struct drm_client_buffer*) ; 
 int /*<<< orphan*/  drm_client_buffer_rmfb (struct drm_client_buffer*) ; 

void drm_client_framebuffer_delete(struct drm_client_buffer *buffer)
{
	if (!buffer)
		return;

	drm_client_buffer_rmfb(buffer);
	drm_client_buffer_delete(buffer);
}