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
struct qcm_process_device {int sh_mem_config; int /*<<< orphan*/  sh_mem_bases; TYPE_2__* pqm; scalar_t__ sh_mem_ape1_base; scalar_t__ sh_mem_ape1_limit; } ;
struct kfd_process_device {int dummy; } ;
struct device_queue_manager {int dummy; } ;
struct TYPE_4__ {TYPE_1__* process; } ;
struct TYPE_3__ {int /*<<< orphan*/  is_32bit_user_mode; } ;

/* Variables and functions */
 int ALIGNMENT_MODE (int /*<<< orphan*/ ) ; 
 int APE1_MTYPE (int /*<<< orphan*/ ) ; 
 int DEFAULT_MTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTYPE_NONCACHED ; 
 int /*<<< orphan*/  SH_MEM_ALIGNMENT_MODE_UNALIGNED ; 
 int /*<<< orphan*/  compute_sh_mem_bases_64bit (unsigned int) ; 
 unsigned int get_sh_mem_bases_nybble_64 (struct kfd_process_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 struct kfd_process_device* qpd_to_pdd (struct qcm_process_device*) ; 

__attribute__((used)) static int update_qpd_cik_hawaii(struct device_queue_manager *dqm,
		struct qcm_process_device *qpd)
{
	struct kfd_process_device *pdd;
	unsigned int temp;

	pdd = qpd_to_pdd(qpd);

	/* check if sh_mem_config register already configured */
	if (qpd->sh_mem_config == 0) {
		qpd->sh_mem_config =
			ALIGNMENT_MODE(SH_MEM_ALIGNMENT_MODE_UNALIGNED) |
			DEFAULT_MTYPE(MTYPE_NONCACHED) |
			APE1_MTYPE(MTYPE_NONCACHED);
		qpd->sh_mem_ape1_limit = 0;
		qpd->sh_mem_ape1_base = 0;
	}

	/* On dGPU we're always in GPUVM64 addressing mode with 64-bit
	 * aperture addresses.
	 */
	temp = get_sh_mem_bases_nybble_64(pdd);
	qpd->sh_mem_bases = compute_sh_mem_bases_64bit(temp);

	pr_debug("is32bit process: %d sh_mem_bases nybble: 0x%X and register 0x%X\n",
		qpd->pqm->process->is_32bit_user_mode, temp, qpd->sh_mem_bases);

	return 0;
}