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
struct amdgpu_device {scalar_t__ in_gpu_reset; } ;
typedef  enum kfd_preempt_type { ____Placeholder_kfd_preempt_type } kfd_preempt_type ;
typedef  enum hqd_dequeue_request_type { ____Placeholder_hqd_dequeue_request_type } hqd_dequeue_request_type ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIVE ; 
 int CP_HQD_ACTIVE__ACTIVE_MASK ; 
 int CP_HQD_DEQUEUE_REQUEST__IQ_REQ_PEND_MASK ; 
 int /*<<< orphan*/  CP_HQD_IQ_TIMER ; 
 int DRAIN_PIPE ; 
 int EIO ; 
 int ETIME ; 
 unsigned int HZ ; 
#define  KFD_PREEMPT_TYPE_WAVEFRONT_DRAIN 129 
#define  KFD_PREEMPT_TYPE_WAVEFRONT_RESET 128 
 int /*<<< orphan*/  PROCESSING_IQ ; 
 int REG_GET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RESET_WAVES ; 
 int /*<<< orphan*/  RETRY_TYPE ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAIT_TIME ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  acquire_queue (struct kgd_dev*,int,int) ; 
 struct amdgpu_device* get_amdgpu_device (struct kgd_dev*) ; 
 unsigned int jiffies ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mmCP_HQD_ACTIVE ; 
 int /*<<< orphan*/  mmCP_HQD_DEQUEUE_REQUEST ; 
 int /*<<< orphan*/  mmCP_HQD_IQ_TIMER ; 
 int /*<<< orphan*/  mmCP_HQD_PQ_DOORBELL_CONTROL ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  release_queue (struct kgd_dev*) ; 
 scalar_t__ time_after (unsigned int,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int kgd_hqd_destroy(struct kgd_dev *kgd, void *mqd,
				enum kfd_preempt_type reset_type,
				unsigned int utimeout, uint32_t pipe_id,
				uint32_t queue_id)
{
	struct amdgpu_device *adev = get_amdgpu_device(kgd);
	uint32_t temp;
	enum hqd_dequeue_request_type type;
	unsigned long flags, end_jiffies;
	int retry;

	if (adev->in_gpu_reset)
		return -EIO;

	acquire_queue(kgd, pipe_id, queue_id);
	WREG32(mmCP_HQD_PQ_DOORBELL_CONTROL, 0);

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

	/* Workaround: If IQ timer is active and the wait time is close to or
	 * equal to 0, dequeueing is not safe. Wait until either the wait time
	 * is larger or timer is cleared. Also, ensure that IQ_REQ_PEND is
	 * cleared before continuing. Also, ensure wait times are set to at
	 * least 0x3.
	 */
	local_irq_save(flags);
	preempt_disable();
	retry = 5000; /* wait for 500 usecs at maximum */
	while (true) {
		temp = RREG32(mmCP_HQD_IQ_TIMER);
		if (REG_GET_FIELD(temp, CP_HQD_IQ_TIMER, PROCESSING_IQ)) {
			pr_debug("HW is processing IQ\n");
			goto loop;
		}
		if (REG_GET_FIELD(temp, CP_HQD_IQ_TIMER, ACTIVE)) {
			if (REG_GET_FIELD(temp, CP_HQD_IQ_TIMER, RETRY_TYPE)
					== 3) /* SEM-rearm is safe */
				break;
			/* Wait time 3 is safe for CP, but our MMIO read/write
			 * time is close to 1 microsecond, so check for 10 to
			 * leave more buffer room
			 */
			if (REG_GET_FIELD(temp, CP_HQD_IQ_TIMER, WAIT_TIME)
					>= 10)
				break;
			pr_debug("IQ timer is active\n");
		} else
			break;
loop:
		if (!retry) {
			pr_err("CP HQD IQ timer status time out\n");
			break;
		}
		ndelay(100);
		--retry;
	}
	retry = 1000;
	while (true) {
		temp = RREG32(mmCP_HQD_DEQUEUE_REQUEST);
		if (!(temp & CP_HQD_DEQUEUE_REQUEST__IQ_REQ_PEND_MASK))
			break;
		pr_debug("Dequeue request is pending\n");

		if (!retry) {
			pr_err("CP HQD dequeue request time out\n");
			break;
		}
		ndelay(100);
		--retry;
	}
	local_irq_restore(flags);
	preempt_enable();

	WREG32(mmCP_HQD_DEQUEUE_REQUEST, type);

	end_jiffies = (utimeout * HZ / 1000) + jiffies;
	while (true) {
		temp = RREG32(mmCP_HQD_ACTIVE);
		if (!(temp & CP_HQD_ACTIVE__ACTIVE_MASK))
			break;
		if (time_after(jiffies, end_jiffies)) {
			pr_err("cp queue preemption time out\n");
			release_queue(kgd);
			return -ETIME;
		}
		usleep_range(500, 1000);
	}

	release_queue(kgd);
	return 0;
}