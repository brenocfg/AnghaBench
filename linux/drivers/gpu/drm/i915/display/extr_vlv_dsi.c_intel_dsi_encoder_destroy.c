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
struct intel_dsi {scalar_t__ gpio_panel; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 struct intel_dsi* enc_to_intel_dsi (struct drm_encoder*) ; 
 int /*<<< orphan*/  gpiod_put (scalar_t__) ; 
 int /*<<< orphan*/  intel_encoder_destroy (struct drm_encoder*) ; 

__attribute__((used)) static void intel_dsi_encoder_destroy(struct drm_encoder *encoder)
{
	struct intel_dsi *intel_dsi = enc_to_intel_dsi(encoder);

	/* dispose of the gpios */
	if (intel_dsi->gpio_panel)
		gpiod_put(intel_dsi->gpio_panel);

	intel_encoder_destroy(encoder);
}