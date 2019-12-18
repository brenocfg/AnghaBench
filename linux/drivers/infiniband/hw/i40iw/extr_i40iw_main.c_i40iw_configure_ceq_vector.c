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
typedef  scalar_t__ u32 ;
struct i40iw_msix_vector {scalar_t__ ceq_id; int /*<<< orphan*/  mask; int /*<<< orphan*/  irq; int /*<<< orphan*/  cpu_affinity; } ;
struct i40iw_device {int /*<<< orphan*/  dpc_tasklet; scalar_t__ msix_shared; } ;
struct i40iw_ceq {int /*<<< orphan*/  dpc_tasklet; scalar_t__ msix_shared; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int I40IW_ERR_CONFIG ; 
 int /*<<< orphan*/  cpumask_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40iw_ceq_dpc ; 
 int /*<<< orphan*/  i40iw_ceq_handler ; 
 int /*<<< orphan*/  i40iw_dpc ; 
 int /*<<< orphan*/  i40iw_irq_handler ; 
 int /*<<< orphan*/  i40iw_pr_err (char*) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct i40iw_device*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_configure_ceq_vector(struct i40iw_device *iwdev,
							 struct i40iw_ceq *iwceq,
							 u32 ceq_id,
							 struct i40iw_msix_vector *msix_vec)
{
	enum i40iw_status_code status;

	if (iwdev->msix_shared && !ceq_id) {
		tasklet_init(&iwdev->dpc_tasklet, i40iw_dpc, (unsigned long)iwdev);
		status = request_irq(msix_vec->irq, i40iw_irq_handler, 0, "AEQCEQ", iwdev);
	} else {
		tasklet_init(&iwceq->dpc_tasklet, i40iw_ceq_dpc, (unsigned long)iwceq);
		status = request_irq(msix_vec->irq, i40iw_ceq_handler, 0, "CEQ", iwceq);
	}

	cpumask_clear(&msix_vec->mask);
	cpumask_set_cpu(msix_vec->cpu_affinity, &msix_vec->mask);
	irq_set_affinity_hint(msix_vec->irq, &msix_vec->mask);

	if (status) {
		i40iw_pr_err("ceq irq config fail\n");
		return I40IW_ERR_CONFIG;
	}
	msix_vec->ceq_id = ceq_id;

	return 0;
}