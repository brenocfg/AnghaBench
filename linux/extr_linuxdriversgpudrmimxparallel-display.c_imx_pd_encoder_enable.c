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
struct imx_parallel_display {int /*<<< orphan*/  panel; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_panel_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_prepare (int /*<<< orphan*/ ) ; 
 struct imx_parallel_display* enc_to_imxpd (struct drm_encoder*) ; 

__attribute__((used)) static void imx_pd_encoder_enable(struct drm_encoder *encoder)
{
	struct imx_parallel_display *imxpd = enc_to_imxpd(encoder);

	drm_panel_prepare(imxpd->panel);
	drm_panel_enable(imxpd->panel);
}