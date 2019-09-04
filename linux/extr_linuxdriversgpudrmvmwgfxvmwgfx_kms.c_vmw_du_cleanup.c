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
struct vmw_display_unit {int /*<<< orphan*/  connector; int /*<<< orphan*/  encoder; int /*<<< orphan*/  crtc; int /*<<< orphan*/  cursor; int /*<<< orphan*/  primary; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_plane_cleanup (int /*<<< orphan*/ *) ; 

void vmw_du_cleanup(struct vmw_display_unit *du)
{
	drm_plane_cleanup(&du->primary);
	drm_plane_cleanup(&du->cursor);

	drm_connector_unregister(&du->connector);
	drm_crtc_cleanup(&du->crtc);
	drm_encoder_cleanup(&du->encoder);
	drm_connector_cleanup(&du->connector);
}