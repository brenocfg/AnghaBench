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
struct drm_device {struct aspeed_gfx* dev_private; } ;
struct aspeed_gfx {int /*<<< orphan*/  connector; int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aspeed_gfx_formats ; 
 int /*<<< orphan*/  aspeed_gfx_funcs ; 
 int drm_simple_display_pipe_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int aspeed_gfx_create_pipe(struct drm_device *drm)
{
	struct aspeed_gfx *priv = drm->dev_private;

	return drm_simple_display_pipe_init(drm, &priv->pipe, &aspeed_gfx_funcs,
					    aspeed_gfx_formats,
					    ARRAY_SIZE(aspeed_gfx_formats),
					    NULL,
					    &priv->connector);
}