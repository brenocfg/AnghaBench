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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dpm_mutex; } ;
struct amdgpu_device {TYPE_1__ virt; } ;

/* Variables and functions */
 int EBADRQC ; 
 int /*<<< orphan*/  IDH_FAIL ; 
 int /*<<< orphan*/  IDH_IRQ_FORCE_DPM_LEVEL ; 
 int /*<<< orphan*/  IDH_SUCCESS ; 
 int /*<<< orphan*/  amdgim_is_hwperf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  xgpu_ai_mailbox_trans_msg (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xgpu_ai_poll_msg (struct amdgpu_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgpu_ai_force_dpm_level(struct amdgpu_device *adev, u32 level)
{
        int r = 0;
        u32 req = IDH_IRQ_FORCE_DPM_LEVEL;

        if (!amdgim_is_hwperf(adev))
                return -EBADRQC;

        mutex_lock(&adev->virt.dpm_mutex);
        xgpu_ai_mailbox_trans_msg(adev, req, level, 0, 0);

        r = xgpu_ai_poll_msg(adev, IDH_SUCCESS);
        if (!r)
                goto out;

        r = xgpu_ai_poll_msg(adev, IDH_FAIL);
        if (!r)
                pr_info("DPM request failed");
        else
                pr_info("Mailbox is broken");

out:
        mutex_unlock(&adev->virt.dpm_mutex);
        return r;
}