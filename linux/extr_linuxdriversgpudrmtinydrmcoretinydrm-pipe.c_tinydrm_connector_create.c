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
struct drm_connector {int /*<<< orphan*/  status; } ;
struct tinydrm_connector {struct drm_connector base; int /*<<< orphan*/  mode; } ;
struct drm_display_mode {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct drm_connector* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  connector_status_connected ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_mode_copy (int /*<<< orphan*/ *,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  kfree (struct tinydrm_connector*) ; 
 struct tinydrm_connector* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tinydrm_connector_funcs ; 
 int /*<<< orphan*/  tinydrm_connector_hfuncs ; 

struct drm_connector *
tinydrm_connector_create(struct drm_device *drm,
			 const struct drm_display_mode *mode,
			 int connector_type)
{
	struct tinydrm_connector *tconn;
	struct drm_connector *connector;
	int ret;

	tconn = kzalloc(sizeof(*tconn), GFP_KERNEL);
	if (!tconn)
		return ERR_PTR(-ENOMEM);

	drm_mode_copy(&tconn->mode, mode);
	connector = &tconn->base;

	drm_connector_helper_add(connector, &tinydrm_connector_hfuncs);
	ret = drm_connector_init(drm, connector, &tinydrm_connector_funcs,
				 connector_type);
	if (ret) {
		kfree(tconn);
		return ERR_PTR(ret);
	}

	connector->status = connector_status_connected;

	return connector;
}