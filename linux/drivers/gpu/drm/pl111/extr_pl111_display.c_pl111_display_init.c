#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pl111_drm_dev_private {int /*<<< orphan*/  connector; TYPE_1__* variant; int /*<<< orphan*/  pipe; } ;
struct drm_device {struct pl111_drm_dev_private* dev_private; } ;
struct TYPE_5__ {int /*<<< orphan*/  disable_vblank; int /*<<< orphan*/  enable_vblank; } ;
struct TYPE_4__ {int /*<<< orphan*/  nformats; int /*<<< orphan*/  formats; int /*<<< orphan*/  broken_vblank; } ;

/* Variables and functions */
 int drm_simple_display_pipe_init (struct drm_device*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pl111_display_disable_vblank ; 
 int /*<<< orphan*/  pl111_display_enable_vblank ; 
 TYPE_2__ pl111_display_funcs ; 
 int pl111_init_clock_divider (struct drm_device*) ; 

int pl111_display_init(struct drm_device *drm)
{
	struct pl111_drm_dev_private *priv = drm->dev_private;
	int ret;

	ret = pl111_init_clock_divider(drm);
	if (ret)
		return ret;

	if (!priv->variant->broken_vblank) {
		pl111_display_funcs.enable_vblank = pl111_display_enable_vblank;
		pl111_display_funcs.disable_vblank = pl111_display_disable_vblank;
	}

	ret = drm_simple_display_pipe_init(drm, &priv->pipe,
					   &pl111_display_funcs,
					   priv->variant->formats,
					   priv->variant->nformats,
					   NULL,
					   priv->connector);
	if (ret)
		return ret;

	return 0;
}