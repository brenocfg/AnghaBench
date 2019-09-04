#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  format; scalar_t__ valid_bank_mask; } ;
struct hv_send_ipi_ex {int vector; TYPE_2__ vp_set; scalar_t__ reserved; } ;
struct cpumask {int dummy; } ;
struct TYPE_3__ {int hints; } ;

/* Variables and functions */
 int /*<<< orphan*/  HVCALL_SEND_IPI_EX ; 
 int /*<<< orphan*/  HV_GENERIC_SET_ALL ; 
 int /*<<< orphan*/  HV_GENERIC_SET_SPARSE_4K ; 
 int HV_X64_EX_PROCESSOR_MASKS_RECOMMENDED ; 
 int /*<<< orphan*/  cpu_present_mask ; 
 int /*<<< orphan*/  cpumask_equal (struct cpumask const*,int /*<<< orphan*/ ) ; 
 int cpumask_to_vpset (TYPE_2__*,struct cpumask const*) ; 
 int hv_do_rep_hypercall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct hv_send_ipi_ex*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hyperv_pcpu_input_arg ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 TYPE_1__ ms_hyperv ; 
 scalar_t__ this_cpu_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool __send_ipi_mask_ex(const struct cpumask *mask, int vector)
{
	struct hv_send_ipi_ex **arg;
	struct hv_send_ipi_ex *ipi_arg;
	unsigned long flags;
	int nr_bank = 0;
	int ret = 1;

	if (!(ms_hyperv.hints & HV_X64_EX_PROCESSOR_MASKS_RECOMMENDED))
		return false;

	local_irq_save(flags);
	arg = (struct hv_send_ipi_ex **)this_cpu_ptr(hyperv_pcpu_input_arg);

	ipi_arg = *arg;
	if (unlikely(!ipi_arg))
		goto ipi_mask_ex_done;

	ipi_arg->vector = vector;
	ipi_arg->reserved = 0;
	ipi_arg->vp_set.valid_bank_mask = 0;

	if (!cpumask_equal(mask, cpu_present_mask)) {
		ipi_arg->vp_set.format = HV_GENERIC_SET_SPARSE_4K;
		nr_bank = cpumask_to_vpset(&(ipi_arg->vp_set), mask);
	}
	if (nr_bank < 0)
		goto ipi_mask_ex_done;
	if (!nr_bank)
		ipi_arg->vp_set.format = HV_GENERIC_SET_ALL;

	ret = hv_do_rep_hypercall(HVCALL_SEND_IPI_EX, 0, nr_bank,
			      ipi_arg, NULL);

ipi_mask_ex_done:
	local_irq_restore(flags);
	return ((ret == 0) ? true : false);
}