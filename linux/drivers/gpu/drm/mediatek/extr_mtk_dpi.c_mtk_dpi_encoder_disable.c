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
struct mtk_dpi {int dummy; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 struct mtk_dpi* mtk_dpi_from_encoder (struct drm_encoder*) ; 
 int /*<<< orphan*/  mtk_dpi_power_off (struct mtk_dpi*) ; 

__attribute__((used)) static void mtk_dpi_encoder_disable(struct drm_encoder *encoder)
{
	struct mtk_dpi *dpi = mtk_dpi_from_encoder(encoder);

	mtk_dpi_power_off(dpi);
}