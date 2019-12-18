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
struct qcm_process_device {int sh_mem_config; int /*<<< orphan*/  sh_mem_bases; scalar_t__ sh_mem_ape1_base; scalar_t__ sh_mem_ape1_limit; } ;
struct kfd_process_device {int dummy; } ;
struct device_queue_manager {int dummy; } ;

/* Variables and functions */
 int SH_MEM_ALIGNMENT_MODE_UNALIGNED ; 
 int SH_MEM_CONFIG__ALIGNMENT_MODE__SHIFT ; 
 int SH_MEM_CONFIG__RETRY_DISABLE__SHIFT ; 
 int /*<<< orphan*/  compute_sh_mem_bases_64bit (struct kfd_process_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 struct kfd_process_device* qpd_to_pdd (struct qcm_process_device*) ; 
 scalar_t__ vega10_noretry ; 

__attribute__((used)) static int update_qpd_v10(struct device_queue_manager *dqm,
			 struct qcm_process_device *qpd)
{
	struct kfd_process_device *pdd;

	pdd = qpd_to_pdd(qpd);

	/* check if sh_mem_config register already configured */
	if (qpd->sh_mem_config == 0) {
		qpd->sh_mem_config =
				SH_MEM_ALIGNMENT_MODE_UNALIGNED <<
					SH_MEM_CONFIG__ALIGNMENT_MODE__SHIFT;
#if 0
		/* TODO:
		 *    This shouldn't be an issue with Navi10.  Verify.
		 */
		if (vega10_noretry)
			qpd->sh_mem_config |=
				1 << SH_MEM_CONFIG__RETRY_DISABLE__SHIFT;
#endif

		qpd->sh_mem_ape1_limit = 0;
		qpd->sh_mem_ape1_base = 0;
	}

	qpd->sh_mem_bases = compute_sh_mem_bases_64bit(pdd);

	pr_debug("sh_mem_bases 0x%X\n", qpd->sh_mem_bases);

	return 0;
}