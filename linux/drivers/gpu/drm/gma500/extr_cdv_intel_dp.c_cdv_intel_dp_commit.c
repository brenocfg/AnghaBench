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
struct gma_encoder {int dummy; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdv_intel_dp_complete_link_train (struct gma_encoder*) ; 
 int /*<<< orphan*/  cdv_intel_dp_start_link_train (struct gma_encoder*) ; 
 int /*<<< orphan*/  cdv_intel_edp_backlight_on (struct gma_encoder*) ; 
 int /*<<< orphan*/  cdv_intel_edp_panel_on (struct gma_encoder*) ; 
 int is_edp (struct gma_encoder*) ; 
 struct gma_encoder* to_gma_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void cdv_intel_dp_commit(struct drm_encoder *encoder)
{
	struct gma_encoder *intel_encoder = to_gma_encoder(encoder);
	int edp = is_edp(intel_encoder);

	if (edp)
		cdv_intel_edp_panel_on(intel_encoder);
	cdv_intel_dp_start_link_train(intel_encoder);
	cdv_intel_dp_complete_link_train(intel_encoder);
	if (edp)
		cdv_intel_edp_backlight_on(intel_encoder);
}