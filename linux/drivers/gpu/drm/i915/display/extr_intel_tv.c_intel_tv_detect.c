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
struct intel_tv {int type; } ;
struct intel_load_detect_pipe {int dummy; } ;
struct drm_modeset_acquire_ctx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_connector {int status; int /*<<< orphan*/  name; TYPE_1__ base; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int connector_status_unknown ; 
 struct intel_tv* intel_attached_tv (struct drm_connector*) ; 
 int intel_get_load_detect_pipe (struct drm_connector*,int /*<<< orphan*/ *,struct intel_load_detect_pipe*,struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  intel_release_load_detect_pipe (struct drm_connector*,struct intel_load_detect_pipe*,struct drm_modeset_acquire_ctx*) ; 
 int intel_tv_detect_type (struct intel_tv*,struct drm_connector*) ; 
 int /*<<< orphan*/  intel_tv_find_better_format (struct drm_connector*) ; 

__attribute__((used)) static int
intel_tv_detect(struct drm_connector *connector,
		struct drm_modeset_acquire_ctx *ctx,
		bool force)
{
	struct intel_tv *intel_tv = intel_attached_tv(connector);
	enum drm_connector_status status;
	int type;

	DRM_DEBUG_KMS("[CONNECTOR:%d:%s] force=%d\n",
		      connector->base.id, connector->name,
		      force);

	if (force) {
		struct intel_load_detect_pipe tmp;
		int ret;

		ret = intel_get_load_detect_pipe(connector, NULL, &tmp, ctx);
		if (ret < 0)
			return ret;

		if (ret > 0) {
			type = intel_tv_detect_type(intel_tv, connector);
			intel_release_load_detect_pipe(connector, &tmp, ctx);
			status = type < 0 ?
				connector_status_disconnected :
				connector_status_connected;
		} else
			status = connector_status_unknown;

		if (status == connector_status_connected) {
			intel_tv->type = type;
			intel_tv_find_better_format(connector);
		}

		return status;
	} else
		return connector->status;
}