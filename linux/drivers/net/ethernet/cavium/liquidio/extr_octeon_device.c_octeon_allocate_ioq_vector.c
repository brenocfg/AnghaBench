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
struct octeon_ioq_vector {int iq_index; int droq_index; int ioq_num; int /*<<< orphan*/  affinity_mask; int /*<<< orphan*/  mbox; struct octeon_device* oct_dev; } ;
struct TYPE_2__ {int pf_srn; } ;
struct octeon_device {scalar_t__ chip_id; TYPE_1__ sriov_info; int /*<<< orphan*/ * mbox; struct octeon_ioq_vector* ioq_vector; } ;

/* Variables and functions */
 scalar_t__ OCTEON_CN23XX_PF_VID ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ *) ; 
 int num_online_cpus () ; 
 struct octeon_ioq_vector* vzalloc (int) ; 

int
octeon_allocate_ioq_vector(struct octeon_device *oct, u32 num_ioqs)
{
	struct octeon_ioq_vector *ioq_vector;
	int cpu_num;
	int size;
	int i;

	size = sizeof(struct octeon_ioq_vector) * num_ioqs;

	oct->ioq_vector = vzalloc(size);
	if (!oct->ioq_vector)
		return -1;
	for (i = 0; i < num_ioqs; i++) {
		ioq_vector		= &oct->ioq_vector[i];
		ioq_vector->oct_dev	= oct;
		ioq_vector->iq_index	= i;
		ioq_vector->droq_index	= i;
		ioq_vector->mbox	= oct->mbox[i];

		cpu_num = i % num_online_cpus();
		cpumask_set_cpu(cpu_num, &ioq_vector->affinity_mask);

		if (oct->chip_id == OCTEON_CN23XX_PF_VID)
			ioq_vector->ioq_num	= i + oct->sriov_info.pf_srn;
		else
			ioq_vector->ioq_num	= i;
	}

	return 0;
}