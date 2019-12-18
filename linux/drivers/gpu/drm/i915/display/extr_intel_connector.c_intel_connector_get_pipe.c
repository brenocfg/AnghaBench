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
struct TYPE_7__ {TYPE_2__* state; struct drm_device* dev; } ;
struct intel_connector {TYPE_3__ base; } ;
struct TYPE_5__ {int /*<<< orphan*/  connection_mutex; } ;
struct drm_device {TYPE_1__ mode_config; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_8__ {int pipe; } ;
struct TYPE_6__ {int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 int INVALID_PIPE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  drm_modeset_is_locked (int /*<<< orphan*/ *) ; 
 TYPE_4__* to_intel_crtc (int /*<<< orphan*/ ) ; 

enum pipe intel_connector_get_pipe(struct intel_connector *connector)
{
	struct drm_device *dev = connector->base.dev;

	WARN_ON(!drm_modeset_is_locked(&dev->mode_config.connection_mutex));

	if (!connector->base.state->crtc)
		return INVALID_PIPE;

	return to_intel_crtc(connector->base.state->crtc)->pipe;
}