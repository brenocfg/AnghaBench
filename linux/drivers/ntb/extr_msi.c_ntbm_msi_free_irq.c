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
struct ntb_dev {int /*<<< orphan*/  dev; } ;
struct msi_desc {int /*<<< orphan*/ * write_msi_msg_data; int /*<<< orphan*/ * write_msi_msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ *,unsigned int,void*) ; 
 int /*<<< orphan*/  devres_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct msi_desc*) ; 
 struct msi_desc* irq_get_msi_desc (unsigned int) ; 
 int /*<<< orphan*/  ntbm_msi_callback_match ; 
 int /*<<< orphan*/  ntbm_msi_callback_release ; 

void ntbm_msi_free_irq(struct ntb_dev *ntb, unsigned int irq, void *dev_id)
{
	struct msi_desc *entry = irq_get_msi_desc(irq);

	entry->write_msi_msg = NULL;
	entry->write_msi_msg_data = NULL;

	WARN_ON(devres_destroy(&ntb->dev, ntbm_msi_callback_release,
			       ntbm_msi_callback_match, entry));

	devm_free_irq(&ntb->dev, irq, dev_id);
}