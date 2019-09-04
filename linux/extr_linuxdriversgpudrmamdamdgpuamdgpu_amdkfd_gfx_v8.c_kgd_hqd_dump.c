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
typedef  int uint32_t ;
struct kgd_dev {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RREG32 (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  acquire_queue (struct kgd_dev*,int,int) ; 
 struct amdgpu_device* get_amdgpu_device (struct kgd_dev*) ; 
 int** kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int mmCOMPUTE_STATIC_THREAD_MGMT_SE0 ; 
 int mmCOMPUTE_STATIC_THREAD_MGMT_SE1 ; 
 int mmCOMPUTE_STATIC_THREAD_MGMT_SE2 ; 
 int mmCOMPUTE_STATIC_THREAD_MGMT_SE3 ; 
 int mmCP_HQD_EOP_DONES ; 
 int mmCP_MQD_BASE_ADDR ; 
 int /*<<< orphan*/  release_queue (struct kgd_dev*) ; 

__attribute__((used)) static int kgd_hqd_dump(struct kgd_dev *kgd,
			uint32_t pipe_id, uint32_t queue_id,
			uint32_t (**dump)[2], uint32_t *n_regs)
{
	struct amdgpu_device *adev = get_amdgpu_device(kgd);
	uint32_t i = 0, reg;
#define HQD_N_REGS (54+4)
#define DUMP_REG(addr) do {				\
		if (WARN_ON_ONCE(i >= HQD_N_REGS))	\
			break;				\
		(*dump)[i][0] = (addr) << 2;		\
		(*dump)[i++][1] = RREG32(addr);		\
	} while (0)

	*dump = kmalloc_array(HQD_N_REGS * 2, sizeof(uint32_t), GFP_KERNEL);
	if (*dump == NULL)
		return -ENOMEM;

	acquire_queue(kgd, pipe_id, queue_id);

	DUMP_REG(mmCOMPUTE_STATIC_THREAD_MGMT_SE0);
	DUMP_REG(mmCOMPUTE_STATIC_THREAD_MGMT_SE1);
	DUMP_REG(mmCOMPUTE_STATIC_THREAD_MGMT_SE2);
	DUMP_REG(mmCOMPUTE_STATIC_THREAD_MGMT_SE3);

	for (reg = mmCP_MQD_BASE_ADDR; reg <= mmCP_HQD_EOP_DONES; reg++)
		DUMP_REG(reg);

	release_queue(kgd);

	WARN_ON_ONCE(i != HQD_N_REGS);
	*n_regs = i;

	return 0;
}