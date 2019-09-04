#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sn_hwperf_op_info {int ret; TYPE_1__* a; } ;
struct TYPE_2__ {int arg; } ;

/* Variables and functions */
 int EINVAL ; 
 int SN_HWPERF_ARG_ANY_CPU ; 
 int SN_HWPERF_ARG_CPU_MASK ; 
 int SN_HWPERF_ARG_OBJID_MASK ; 
 int SN_HWPERF_ARG_USE_IPI_MASK ; 
 int /*<<< orphan*/  cpu_online (int) ; 
 int get_cpu () ; 
 int nr_cpu_ids ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  smp_call_function_single (int,int /*<<< orphan*/  (*) (struct sn_hwperf_op_info*),struct sn_hwperf_op_info*,int) ; 
 int /*<<< orphan*/  sn_hwperf_call_sal (struct sn_hwperf_op_info*) ; 
 int /*<<< orphan*/  sn_hwperf_call_sal_work ; 
 int /*<<< orphan*/  work_on_cpu_safe (int,int /*<<< orphan*/ ,struct sn_hwperf_op_info*) ; 

__attribute__((used)) static int sn_hwperf_op_cpu(struct sn_hwperf_op_info *op_info)
{
	u32 cpu;
	u32 use_ipi;
	int r = 0;
	
	cpu = (op_info->a->arg & SN_HWPERF_ARG_CPU_MASK) >> 32;
	use_ipi = op_info->a->arg & SN_HWPERF_ARG_USE_IPI_MASK;
	op_info->a->arg &= SN_HWPERF_ARG_OBJID_MASK;

	if (cpu != SN_HWPERF_ARG_ANY_CPU) {
		if (cpu >= nr_cpu_ids || !cpu_online(cpu)) {
			r = -EINVAL;
			goto out;
		}
	}

	if (cpu == SN_HWPERF_ARG_ANY_CPU) {
		/* don't care which cpu */
		sn_hwperf_call_sal(op_info);
	} else if (cpu == get_cpu()) {
		/* already on correct cpu */
		sn_hwperf_call_sal(op_info);
		put_cpu();
	} else {
		put_cpu();
		if (use_ipi) {
			/* use an interprocessor interrupt to call SAL */
			smp_call_function_single(cpu, sn_hwperf_call_sal,
				op_info, 1);
		} else {
			/* Call on the target CPU */
			work_on_cpu_safe(cpu, sn_hwperf_call_sal_work, op_info);
		}
	}
	r = op_info->ret;

out:
	return r;
}