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
typedef  int /*<<< orphan*/  u32 ;
struct gsc_scaler {int /*<<< orphan*/  main_vratio; int /*<<< orphan*/  main_hratio; } ;
struct gsc_context {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GSC_MAIN_H_RATIO ; 
 int /*<<< orphan*/  GSC_MAIN_H_RATIO_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GSC_MAIN_V_RATIO ; 
 int /*<<< orphan*/  GSC_MAIN_V_RATIO_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsc_set_h_coef (struct gsc_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsc_set_v_coef (struct gsc_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsc_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gsc_set_scaler(struct gsc_context *ctx, struct gsc_scaler *sc)
{
	u32 cfg;

	DRM_DEV_DEBUG_KMS(ctx->dev, "main_hratio[%ld]main_vratio[%ld]\n",
			  sc->main_hratio, sc->main_vratio);

	gsc_set_h_coef(ctx, sc->main_hratio);
	cfg = GSC_MAIN_H_RATIO_VALUE(sc->main_hratio);
	gsc_write(cfg, GSC_MAIN_H_RATIO);

	gsc_set_v_coef(ctx, sc->main_vratio);
	cfg = GSC_MAIN_V_RATIO_VALUE(sc->main_vratio);
	gsc_write(cfg, GSC_MAIN_V_RATIO);
}