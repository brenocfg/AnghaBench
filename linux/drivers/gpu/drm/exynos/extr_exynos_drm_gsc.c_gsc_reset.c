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
struct gsc_scaler {int range; } ;
struct gsc_context {struct gsc_scaler sc; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int gsc_sw_reset (struct gsc_context*) ; 
 int /*<<< orphan*/  memset (struct gsc_scaler*,int,int) ; 

__attribute__((used)) static int gsc_reset(struct gsc_context *ctx)
{
	struct gsc_scaler *sc = &ctx->sc;
	int ret;

	/* reset h/w block */
	ret = gsc_sw_reset(ctx);
	if (ret < 0) {
		dev_err(ctx->dev, "failed to reset hardware.\n");
		return ret;
	}

	/* scaler setting */
	memset(&ctx->sc, 0x0, sizeof(ctx->sc));
	sc->range = true;

	return 0;
}