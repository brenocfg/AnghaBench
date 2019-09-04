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
struct ocxl_context {int dummy; } ;
struct afu_irq {int /*<<< orphan*/  virq; int /*<<< orphan*/ * name; int /*<<< orphan*/  hw_irq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  afu_irq_handler ; 
 int /*<<< orphan*/  irq_create_mapping (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct afu_irq*) ; 

__attribute__((used)) static int setup_afu_irq(struct ocxl_context *ctx, struct afu_irq *irq)
{
	int rc;

	irq->virq = irq_create_mapping(NULL, irq->hw_irq);
	if (!irq->virq) {
		pr_err("irq_create_mapping failed\n");
		return -ENOMEM;
	}
	pr_debug("hw_irq %d mapped to virq %u\n", irq->hw_irq, irq->virq);

	irq->name = kasprintf(GFP_KERNEL, "ocxl-afu-%u", irq->virq);
	if (!irq->name) {
		irq_dispose_mapping(irq->virq);
		return -ENOMEM;
	}

	rc = request_irq(irq->virq, afu_irq_handler, 0, irq->name, irq);
	if (rc) {
		kfree(irq->name);
		irq->name = NULL;
		irq_dispose_mapping(irq->virq);
		pr_err("request_irq failed: %d\n", rc);
		return rc;
	}
	return 0;
}