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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int (* get_halt_ctrl ) (struct dpu_hw_vbif*,int /*<<< orphan*/ ) ;} ;
struct dpu_hw_vbif {scalar_t__ idx; TYPE_2__ ops; TYPE_1__* cap; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_3__ {int /*<<< orphan*/  xin_halt_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPU_ERROR (char*,int,...) ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 scalar_t__ VBIF_0 ; 
 int /*<<< orphan*/  ktime_add_us (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_compare_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int stub1 (struct dpu_hw_vbif*,int /*<<< orphan*/ ) ; 
 int stub2 (struct dpu_hw_vbif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int _dpu_vbif_wait_for_xin_halt(struct dpu_hw_vbif *vbif, u32 xin_id)
{
	ktime_t timeout;
	bool status;
	int rc;

	if (!vbif || !vbif->cap || !vbif->ops.get_halt_ctrl) {
		DPU_ERROR("invalid arguments vbif %d\n", vbif != 0);
		return -EINVAL;
	}

	timeout = ktime_add_us(ktime_get(), vbif->cap->xin_halt_timeout);
	for (;;) {
		status = vbif->ops.get_halt_ctrl(vbif, xin_id);
		if (status)
			break;
		if (ktime_compare_safe(ktime_get(), timeout) > 0) {
			status = vbif->ops.get_halt_ctrl(vbif, xin_id);
			break;
		}
		usleep_range(501, 1000);
	}

	if (!status) {
		rc = -ETIMEDOUT;
		DPU_ERROR("VBIF %d client %d not halting. TIMEDOUT.\n",
				vbif->idx - VBIF_0, xin_id);
	} else {
		rc = 0;
		DPU_DEBUG("VBIF %d client %d is halted\n",
				vbif->idx - VBIF_0, xin_id);
	}

	return rc;
}