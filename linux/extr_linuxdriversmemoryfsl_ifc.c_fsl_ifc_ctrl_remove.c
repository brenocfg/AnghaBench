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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct fsl_ifc_ctrl {int /*<<< orphan*/  gregs; int /*<<< orphan*/  irq; int /*<<< orphan*/  nand_irq; } ;

/* Variables and functions */
 struct fsl_ifc_ctrl* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct fsl_ifc_ctrl*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fsl_ifc_ctrl*) ; 

__attribute__((used)) static int fsl_ifc_ctrl_remove(struct platform_device *dev)
{
	struct fsl_ifc_ctrl *ctrl = dev_get_drvdata(&dev->dev);

	free_irq(ctrl->nand_irq, ctrl);
	free_irq(ctrl->irq, ctrl);

	irq_dispose_mapping(ctrl->nand_irq);
	irq_dispose_mapping(ctrl->irq);

	iounmap(ctrl->gregs);

	dev_set_drvdata(&dev->dev, NULL);
	kfree(ctrl);

	return 0;
}