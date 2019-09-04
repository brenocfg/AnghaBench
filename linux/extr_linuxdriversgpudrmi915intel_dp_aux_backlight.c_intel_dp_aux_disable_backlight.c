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
struct drm_connector_state {int /*<<< orphan*/  best_encoder; } ;

/* Variables and functions */
 int /*<<< orphan*/  enc_to_intel_dp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_aux_backlight_enable (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void intel_dp_aux_disable_backlight(const struct drm_connector_state *old_conn_state)
{
	set_aux_backlight_enable(enc_to_intel_dp(old_conn_state->best_encoder), false);
}