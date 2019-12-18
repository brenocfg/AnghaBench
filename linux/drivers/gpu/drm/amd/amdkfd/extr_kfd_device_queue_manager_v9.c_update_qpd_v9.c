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
struct qcm_process_device {int sh_mem_config; int /*<<< orphan*/  sh_mem_bases; scalar_t__ sh_mem_ape1_base; scalar_t__ sh_mem_ape1_limit; } ;
struct kfd_process_device {int dummy; } ;
struct device_queue_manager {TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  needs_iommu_device; } ;
struct TYPE_3__ {TYPE_2__* device_info; } ;

/* Variables and functions */
 int SH_MEM_ALIGNMENT_MODE_UNALIGNED ; 
 int SH_MEM_CONFIG__ALIGNMENT_MODE__SHIFT ; 
 int SH_MEM_CONFIG__RETRY_DISABLE__SHIFT ; 
 scalar_t__ amdgpu_noretry ; 
 int /*<<< orphan*/  compute_sh_mem_bases_64bit (struct kfd_process_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 struct kfd_process_device* qpd_to_pdd (struct qcm_process_device*) ; 

__attribute__((used)) static int update_qpd_v9(struct device_queue_manager *dqm,
			 struct qcm_process_device *qpd)
{
	struct kfd_process_device *pdd;

	pdd = qpd_to_pdd(qpd);

	/* check if sh_mem_config register already configured */
	if (qpd->sh_mem_config == 0) {
		qpd->sh_mem_config =
				SH_MEM_ALIGNMENT_MODE_UNALIGNED <<
					SH_MEM_CONFIG__ALIGNMENT_MODE__SHIFT;
		if (amdgpu_noretry &&
		    !dqm->dev->device_info->needs_iommu_device)
			qpd->sh_mem_config |=
				1 << SH_MEM_CONFIG__RETRY_DISABLE__SHIFT;

		qpd->sh_mem_ape1_limit = 0;
		qpd->sh_mem_ape1_base = 0;
	}

	qpd->sh_mem_bases = compute_sh_mem_bases_64bit(pdd);

	pr_debug("sh_mem_bases 0x%X\n", qpd->sh_mem_bases);

	return 0;
}