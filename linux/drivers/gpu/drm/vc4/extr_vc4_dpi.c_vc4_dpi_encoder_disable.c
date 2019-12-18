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
struct vc4_dpi_encoder {struct vc4_dpi* dpi; } ;
struct vc4_dpi {int /*<<< orphan*/  pixel_clock; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct vc4_dpi_encoder* to_vc4_dpi_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void vc4_dpi_encoder_disable(struct drm_encoder *encoder)
{
	struct vc4_dpi_encoder *vc4_encoder = to_vc4_dpi_encoder(encoder);
	struct vc4_dpi *dpi = vc4_encoder->dpi;

	clk_disable_unprepare(dpi->pixel_clock);
}