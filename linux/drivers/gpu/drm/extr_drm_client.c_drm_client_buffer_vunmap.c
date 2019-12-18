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
struct drm_client_buffer {int /*<<< orphan*/ * vaddr; int /*<<< orphan*/  gem; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_vunmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void drm_client_buffer_vunmap(struct drm_client_buffer *buffer)
{
	drm_gem_vunmap(buffer->gem, buffer->vaddr);
	buffer->vaddr = NULL;
}