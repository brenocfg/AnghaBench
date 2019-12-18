#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {scalar_t__ p_pf2vf; } ;
struct TYPE_6__ {int /*<<< orphan*/  dpm_mutex; TYPE_2__ fw_reserve; } ;
struct TYPE_4__ {int /*<<< orphan*/ * va; } ;
struct amdgpu_device {TYPE_3__ virt; TYPE_1__ fw_vram_usage; } ;

/* Variables and functions */
 int EBADRQC ; 
 int /*<<< orphan*/  IDH_FAIL ; 
 int IDH_IRQ_GET_PP_MCLK ; 
 int IDH_IRQ_GET_PP_SCLK ; 
 int /*<<< orphan*/  IDH_SUCCESS ; 
 int /*<<< orphan*/  NBIO ; 
 int PAGE_SIZE ; 
#define  PP_MCLK 129 
#define  PP_SCLK 128 
 int RREG32_NO_KIQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgim_is_hwperf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmBIF_BX_PF0_MAILBOX_MSGBUF_RCV_DW1 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strnlen (char*,int) ; 
 int /*<<< orphan*/  xgpu_ai_mailbox_trans_msg (struct amdgpu_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xgpu_ai_poll_msg (struct amdgpu_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgpu_ai_get_pp_clk(struct amdgpu_device *adev, u32 type, char *buf)
{
        int r = 0;
        u32 req, val, size;

        if (!amdgim_is_hwperf(adev) || buf == NULL)
                return -EBADRQC;

        switch(type) {
        case PP_SCLK:
                req = IDH_IRQ_GET_PP_SCLK;
                break;
        case PP_MCLK:
                req = IDH_IRQ_GET_PP_MCLK;
                break;
        default:
                return -EBADRQC;
        }

        mutex_lock(&adev->virt.dpm_mutex);

        xgpu_ai_mailbox_trans_msg(adev, req, 0, 0, 0);

        r = xgpu_ai_poll_msg(adev, IDH_SUCCESS);
        if (!r && adev->fw_vram_usage.va != NULL) {
                val = RREG32_NO_KIQ(
                        SOC15_REG_OFFSET(NBIO, 0,
                                         mmBIF_BX_PF0_MAILBOX_MSGBUF_RCV_DW1));
                size = strnlen((((char *)adev->virt.fw_reserve.p_pf2vf) +
                                val), PAGE_SIZE);

                if (size < PAGE_SIZE)
                        strcpy(buf,((char *)adev->virt.fw_reserve.p_pf2vf + val));
                else
                        size = 0;

                r = size;
                goto out;
        }

        r = xgpu_ai_poll_msg(adev, IDH_FAIL);
        if(r)
                pr_info("%s DPM request failed",
                        (type == PP_SCLK)? "SCLK" : "MCLK");

out:
        mutex_unlock(&adev->virt.dpm_mutex);
        return r;
}