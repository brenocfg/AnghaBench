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
typedef  int /*<<< orphan*/  u64 ;
struct msi_msg {int /*<<< orphan*/  data; int /*<<< orphan*/  address_hi; int /*<<< orphan*/  address_lo; } ;
struct its_node {int /*<<< orphan*/  (* get_msi_base ) (struct its_device*) ;} ;
struct its_device {struct its_node* its; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iommu_dma_compose_msi_msg (int /*<<< orphan*/ ,struct msi_msg*) ; 
 struct its_device* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_data_get_msi_desc (struct irq_data*) ; 
 int /*<<< orphan*/  its_get_event_id (struct irq_data*) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct its_device*) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void its_irq_compose_msi_msg(struct irq_data *d, struct msi_msg *msg)
{
	struct its_device *its_dev = irq_data_get_irq_chip_data(d);
	struct its_node *its;
	u64 addr;

	its = its_dev->its;
	addr = its->get_msi_base(its_dev);

	msg->address_lo		= lower_32_bits(addr);
	msg->address_hi		= upper_32_bits(addr);
	msg->data		= its_get_event_id(d);

	iommu_dma_compose_msi_msg(irq_data_get_msi_desc(d), msg);
}