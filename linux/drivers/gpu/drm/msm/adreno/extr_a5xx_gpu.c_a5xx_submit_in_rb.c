#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint32_t ;
struct msm_ringbuffer {TYPE_4__* memptrs; } ;
struct msm_gpu {TYPE_1__* dev; } ;
struct msm_gem_submit {unsigned int nr_cmds; int /*<<< orphan*/  seqno; TYPE_3__* cmd; TYPE_2__* bos; struct msm_ringbuffer* ring; } ;
struct msm_gem_object {int /*<<< orphan*/  base; } ;
struct msm_file_private {int dummy; } ;
struct msm_drm_private {struct msm_file_private* lastctx; } ;
struct TYPE_8__ {int /*<<< orphan*/  fence; } ;
struct TYPE_7__ {int type; size_t idx; unsigned int size; } ;
struct TYPE_6__ {struct msm_gem_object* obj; } ;
struct TYPE_5__ {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
#define  MSM_SUBMIT_CMD_BUF 130 
#define  MSM_SUBMIT_CMD_CTX_RESTORE_BUF 129 
#define  MSM_SUBMIT_CMD_IB_TARGET_BUF 128 
 int /*<<< orphan*/  OUT_RING (struct msm_ringbuffer*,unsigned int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  a5xx_flush (struct msm_gpu*,struct msm_ringbuffer*) ; 
 int /*<<< orphan*/  a5xx_idle (struct msm_gpu*,struct msm_ringbuffer*) ; 
 int /*<<< orphan*/  a5xx_preempt_trigger (struct msm_gpu*) ; 
 int /*<<< orphan*/  adreno_wait_ring (struct msm_ringbuffer*,int) ; 
 unsigned int* msm_gem_get_vaddr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_gem_put_vaddr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_gpu_retire (struct msm_gpu*) ; 

__attribute__((used)) static void a5xx_submit_in_rb(struct msm_gpu *gpu, struct msm_gem_submit *submit,
	struct msm_file_private *ctx)
{
	struct msm_drm_private *priv = gpu->dev->dev_private;
	struct msm_ringbuffer *ring = submit->ring;
	struct msm_gem_object *obj;
	uint32_t *ptr, dwords;
	unsigned int i;

	for (i = 0; i < submit->nr_cmds; i++) {
		switch (submit->cmd[i].type) {
		case MSM_SUBMIT_CMD_IB_TARGET_BUF:
			break;
		case MSM_SUBMIT_CMD_CTX_RESTORE_BUF:
			if (priv->lastctx == ctx)
				break;
			/* fall-thru */
		case MSM_SUBMIT_CMD_BUF:
			/* copy commands into RB: */
			obj = submit->bos[submit->cmd[i].idx].obj;
			dwords = submit->cmd[i].size;

			ptr = msm_gem_get_vaddr(&obj->base);

			/* _get_vaddr() shouldn't fail at this point,
			 * since we've already mapped it once in
			 * submit_reloc()
			 */
			if (WARN_ON(!ptr))
				return;

			for (i = 0; i < dwords; i++) {
				/* normally the OUT_PKTn() would wait
				 * for space for the packet.  But since
				 * we just OUT_RING() the whole thing,
				 * need to call adreno_wait_ring()
				 * ourself:
				 */
				adreno_wait_ring(ring, 1);
				OUT_RING(ring, ptr[i]);
			}

			msm_gem_put_vaddr(&obj->base);

			break;
		}
	}

	a5xx_flush(gpu, ring);
	a5xx_preempt_trigger(gpu);

	/* we might not necessarily have a cmd from userspace to
	 * trigger an event to know that submit has completed, so
	 * do this manually:
	 */
	a5xx_idle(gpu, ring);
	ring->memptrs->fence = submit->seqno;
	msm_gpu_retire(gpu);
}