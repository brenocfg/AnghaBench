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
typedef  int u32 ;
struct gsc_context {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  GSC_IRQ ; 
 int GSC_IRQ_ENABLE ; 
 int GSC_IRQ_FRMDONE_MASK ; 
 int GSC_IRQ_OR_MASK ; 
 int gsc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsc_write (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gsc_handle_irq(struct gsc_context *ctx, bool enable,
		bool overflow, bool done)
{
	u32 cfg;

	DRM_DEV_DEBUG_KMS(ctx->dev, "enable[%d]overflow[%d]level[%d]\n",
			  enable, overflow, done);

	cfg = gsc_read(GSC_IRQ);
	cfg |= (GSC_IRQ_OR_MASK | GSC_IRQ_FRMDONE_MASK);

	if (enable)
		cfg |= GSC_IRQ_ENABLE;
	else
		cfg &= ~GSC_IRQ_ENABLE;

	if (overflow)
		cfg &= ~GSC_IRQ_OR_MASK;
	else
		cfg |= GSC_IRQ_OR_MASK;

	if (done)
		cfg &= ~GSC_IRQ_FRMDONE_MASK;
	else
		cfg |= GSC_IRQ_FRMDONE_MASK;

	gsc_write(cfg, GSC_IRQ);
}