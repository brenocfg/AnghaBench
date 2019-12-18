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
struct mtk_dsi {int dummy; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 struct mtk_dsi* encoder_to_dsi (struct drm_encoder*) ; 
 int /*<<< orphan*/  mtk_output_dsi_enable (struct mtk_dsi*) ; 

__attribute__((used)) static void mtk_dsi_encoder_enable(struct drm_encoder *encoder)
{
	struct mtk_dsi *dsi = encoder_to_dsi(encoder);

	mtk_output_dsi_enable(dsi);
}