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
struct nouveau_drm {TYPE_1__* fbcon; } ;
struct drm_connector {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  helper; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_register (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_fb_helper_add_one_connector (int /*<<< orphan*/ *,struct drm_connector*) ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nv50_mstm_register_connector(struct drm_connector *connector)
{
	struct nouveau_drm *drm = nouveau_drm(connector->dev);

	drm_fb_helper_add_one_connector(&drm->fbcon->helper, connector);

	drm_connector_register(connector);
}