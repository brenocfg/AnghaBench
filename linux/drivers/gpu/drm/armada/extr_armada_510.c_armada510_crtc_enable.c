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
struct drm_display_mode {int dummy; } ;
struct armada_crtc {scalar_t__ clk; struct armada510_variant_data* variant_data; } ;
struct armada510_variant_data {scalar_t__ sel_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (scalar_t__) ; 

__attribute__((used)) static void armada510_crtc_enable(struct armada_crtc *dcrtc,
	const struct drm_display_mode *mode)
{
	struct armada510_variant_data *v = dcrtc->variant_data;

	if (!dcrtc->clk && v->sel_clk) {
		if (!WARN_ON(clk_prepare_enable(v->sel_clk)))
			dcrtc->clk = v->sel_clk;
	}
}