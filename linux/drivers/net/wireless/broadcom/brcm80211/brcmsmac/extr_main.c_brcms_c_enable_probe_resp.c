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
struct brcms_c_info {int prb_resp_timeout; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int BRCMS_PRB_RESP_TIMEOUT ; 
 int /*<<< orphan*/  M_PRS_MAXTIME ; 
 int /*<<< orphan*/  brcms_b_write_shm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void brcms_c_enable_probe_resp(struct brcms_c_info *wlc, bool enable)
{
	/*
	 * prevent ucode from sending probe responses by setting the timeout
	 * to 1, it can not send it in that time frame.
	 */
	wlc->prb_resp_timeout = enable ? BRCMS_PRB_RESP_TIMEOUT : 1;
	brcms_b_write_shm(wlc->hw, M_PRS_MAXTIME, wlc->prb_resp_timeout);
	/* TODO: if (enable) => also deactivate receiving of probe request */
}