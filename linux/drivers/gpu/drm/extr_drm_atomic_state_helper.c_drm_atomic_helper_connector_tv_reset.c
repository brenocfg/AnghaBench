#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  top; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
struct TYPE_4__ {TYPE_3__ margins; } ;
struct drm_connector_state {TYPE_1__ tv; } ;
struct TYPE_5__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  top; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
struct drm_cmdline_mode {TYPE_2__ tv_margins; } ;
struct drm_connector {struct drm_connector_state* state; struct drm_cmdline_mode cmdline_mode; } ;

/* Variables and functions */

void drm_atomic_helper_connector_tv_reset(struct drm_connector *connector)
{
	struct drm_cmdline_mode *cmdline = &connector->cmdline_mode;
	struct drm_connector_state *state = connector->state;

	state->tv.margins.left = cmdline->tv_margins.left;
	state->tv.margins.right = cmdline->tv_margins.right;
	state->tv.margins.top = cmdline->tv_margins.top;
	state->tv.margins.bottom = cmdline->tv_margins.bottom;
}