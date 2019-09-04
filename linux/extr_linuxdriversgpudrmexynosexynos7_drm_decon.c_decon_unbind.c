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
struct device {int dummy; } ;
struct decon_context {scalar_t__ encoder; int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  decon_ctx_remove (struct decon_context*) ; 
 int /*<<< orphan*/  decon_disable (int /*<<< orphan*/ ) ; 
 struct decon_context* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  exynos_dpi_remove (scalar_t__) ; 

__attribute__((used)) static void decon_unbind(struct device *dev, struct device *master,
			void *data)
{
	struct decon_context *ctx = dev_get_drvdata(dev);

	decon_disable(ctx->crtc);

	if (ctx->encoder)
		exynos_dpi_remove(ctx->encoder);

	decon_ctx_remove(ctx);
}