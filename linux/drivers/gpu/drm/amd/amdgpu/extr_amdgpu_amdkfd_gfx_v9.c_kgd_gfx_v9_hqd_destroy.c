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
struct v9_mqd {scalar_t__ cp_hqd_vmid; } ;
struct kgd_dev {int dummy; } ;
struct amdgpu_device {scalar_t__ in_gpu_reset; } ;
typedef  enum kfd_preempt_type { ____Placeholder_kfd_preempt_type } kfd_preempt_type ;
typedef  enum hqd_dequeue_request_type { ____Placeholder_hqd_dequeue_request_type } hqd_dequeue_request_type ;

/* Variables and functions */
 int CP_HQD_ACTIVE__ACTIVE_MASK ; 
 int DRAIN_PIPE ; 
 int EIO ; 
 int ETIME ; 
 int /*<<< orphan*/  GC ; 
 unsigned int HZ ; 
#define  KFD_PREEMPT_TYPE_WAVEFRONT_DRAIN 129 
#define  KFD_PREEMPT_TYPE_WAVEFRONT_RESET 128 
 int RESET_WAVES ; 
 int /*<<< orphan*/  RLC_CP_SCHEDULERS ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_FIELD15_RLC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_RLC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  acquire_queue (struct kgd_dev*,int,int) ; 
 struct amdgpu_device* get_amdgpu_device (struct kgd_dev*) ; 
 struct v9_mqd* get_mqd (void*) ; 
 unsigned int jiffies ; 
 int /*<<< orphan*/  mmCP_HQD_ACTIVE ; 
 int /*<<< orphan*/  mmCP_HQD_DEQUEUE_REQUEST ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  release_queue (struct kgd_dev*) ; 
 int /*<<< orphan*/  scheduler1 ; 
 scalar_t__ time_after (unsigned int,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int kgd_gfx_v9_hqd_destroy(struct kgd_dev *kgd, void *mqd,
				enum kfd_preempt_type reset_type,
				unsigned int utimeout, uint32_t pipe_id,
				uint32_t queue_id)
{
	struct amdgpu_device *adev = get_amdgpu_device(kgd);
	enum hqd_dequeue_request_type type;
	unsigned long end_jiffies;
	uint32_t temp;
	struct v9_mqd *m = get_mqd(mqd);

	if (adev->in_gpu_reset)
		return -EIO;

	acquire_queue(kgd, pipe_id, queue_id);

	if (m->cp_hqd_vmid == 0)
		WREG32_FIELD15_RLC(GC, 0, RLC_CP_SCHEDULERS, scheduler1, 0);

	switch (reset_type) {
	case KFD_PREEMPT_TYPE_WAVEFRONT_DRAIN:
		type = DRAIN_PIPE;
		break;
	case KFD_PREEMPT_TYPE_WAVEFRONT_RESET:
		type = RESET_WAVES;
		break;
	default:
		type = DRAIN_PIPE;
		break;
	}

	WREG32_RLC(SOC15_REG_OFFSET(GC, 0, mmCP_HQD_DEQUEUE_REQUEST), type);

	end_jiffies = (utimeout * HZ / 1000) + jiffies;
	while (true) {
		temp = RREG32(SOC15_REG_OFFSET(GC, 0, mmCP_HQD_ACTIVE));
		if (!(temp & CP_HQD_ACTIVE__ACTIVE_MASK))
			break;
		if (time_after(jiffies, end_jiffies)) {
			pr_err("cp queue preemption time out.\n");
			release_queue(kgd);
			return -ETIME;
		}
		usleep_range(500, 1000);
	}

	release_queue(kgd);
	return 0;
}