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
struct dw_dsi {int enable; struct dsi_hw_ctx* ctx; } ;
struct dsi_hw_ctx {int /*<<< orphan*/  pclk; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_mipi_init (struct dw_dsi*) ; 
 struct dw_dsi* encoder_to_dsi (struct drm_encoder*) ; 

__attribute__((used)) static void dsi_encoder_enable(struct drm_encoder *encoder)
{
	struct dw_dsi *dsi = encoder_to_dsi(encoder);
	struct dsi_hw_ctx *ctx = dsi->ctx;
	int ret;

	if (dsi->enable)
		return;

	ret = clk_prepare_enable(ctx->pclk);
	if (ret) {
		DRM_ERROR("fail to enable pclk: %d\n", ret);
		return;
	}

	dsi_mipi_init(dsi);

	dsi->enable = true;
}