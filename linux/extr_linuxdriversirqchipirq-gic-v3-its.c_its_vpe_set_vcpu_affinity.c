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
struct its_vpe {int dummy; } ;
struct its_cmd_info {int cmd_type; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
#define  DESCHEDULE_VPE 130 
 int EINVAL ; 
#define  INVALL_VPE 129 
#define  SCHEDULE_VPE 128 
 struct its_vpe* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  its_vpe_deschedule (struct its_vpe*) ; 
 int /*<<< orphan*/  its_vpe_invall (struct its_vpe*) ; 
 int /*<<< orphan*/  its_vpe_schedule (struct its_vpe*) ; 

__attribute__((used)) static int its_vpe_set_vcpu_affinity(struct irq_data *d, void *vcpu_info)
{
	struct its_vpe *vpe = irq_data_get_irq_chip_data(d);
	struct its_cmd_info *info = vcpu_info;

	switch (info->cmd_type) {
	case SCHEDULE_VPE:
		its_vpe_schedule(vpe);
		return 0;

	case DESCHEDULE_VPE:
		its_vpe_deschedule(vpe);
		return 0;

	case INVALL_VPE:
		its_vpe_invall(vpe);
		return 0;

	default:
		return -EINVAL;
	}
}