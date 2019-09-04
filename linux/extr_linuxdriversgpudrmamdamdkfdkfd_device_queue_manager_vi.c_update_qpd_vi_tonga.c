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
 int MTYPE_UC ; 
 int SH_MEM_ALIGNMENT_MODE_UNALIGNED ; 
 int SH_MEM_CONFIG__ALIGNMENT_MODE__SHIFT ; 
 int SH_MEM_CONFIG__APE1_MTYPE__SHIFT ; 
 int SH_MEM_CONFIG__DEFAULT_MTYPE__SHIFT ; 
 int /*<<< orphan*/  compute_sh_mem_bases_64bit (unsigned int) ; 
 unsigned int get_sh_mem_bases_nybble_64 (struct kfd_process_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,int /*<<< orphan*/ ) ; 
 struct kfd_process_device* qpd_to_pdd (struct qcm_process_device*) ; 

__attribute__((used)) static int update_qpd_vi_tonga(struct device_queue_manager *dqm,
			struct qcm_process_device *qpd)
{
	struct kfd_process_device *pdd;
	unsigned int temp;

	pdd = qpd_to_pdd(qpd);

	/* check if sh_mem_config register already configured */
	if (qpd->sh_mem_config == 0) {
		qpd->sh_mem_config =
				SH_MEM_ALIGNMENT_MODE_UNALIGNED <<
					SH_MEM_CONFIG__ALIGNMENT_MODE__SHIFT |
				MTYPE_UC <<
					SH_MEM_CONFIG__DEFAULT_MTYPE__SHIFT |
				MTYPE_UC <<
					SH_MEM_CONFIG__APE1_MTYPE__SHIFT;

		qpd->sh_mem_ape1_limit = 0;
		qpd->sh_mem_ape1_base = 0;
	}

	/* On dGPU we're always in GPUVM64 addressing mode with 64-bit
	 * aperture addresses.
	 */
	temp = get_sh_mem_bases_nybble_64(pdd);
	qpd->sh_mem_bases = compute_sh_mem_bases_64bit(temp);

	pr_debug("sh_mem_bases nybble: 0x%X and register 0x%X\n",
		temp, qpd->sh_mem_bases);

	return 0;
}