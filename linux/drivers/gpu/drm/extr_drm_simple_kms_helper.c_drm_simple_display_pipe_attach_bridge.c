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
struct drm_simple_display_pipe {int /*<<< orphan*/  encoder; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 int drm_bridge_attach (int /*<<< orphan*/ *,struct drm_bridge*,int /*<<< orphan*/ *) ; 

int drm_simple_display_pipe_attach_bridge(struct drm_simple_display_pipe *pipe,
					  struct drm_bridge *bridge)
{
	return drm_bridge_attach(&pipe->encoder, bridge, NULL);
}