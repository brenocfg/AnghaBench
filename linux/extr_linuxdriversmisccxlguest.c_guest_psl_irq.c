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
struct cxl_irq_info {int dummy; } ;
struct cxl_context {int /*<<< orphan*/  pe; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int IRQ_HANDLED ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int cxl_irq_psl8 (int,struct cxl_context*,struct cxl_irq_info*) ; 
 int guest_get_irq_info (struct cxl_context*,struct cxl_irq_info*) ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t guest_psl_irq(int irq, void *data)
{
	struct cxl_context *ctx = data;
	struct cxl_irq_info irq_info;
	int rc;

	pr_devel("%d: received PSL interrupt %i\n", ctx->pe, irq);
	rc = guest_get_irq_info(ctx, &irq_info);
	if (rc) {
		WARN(1, "Unable to get IRQ info: %i\n", rc);
		return IRQ_HANDLED;
	}

	rc = cxl_irq_psl8(irq, ctx, &irq_info);
	return rc;
}