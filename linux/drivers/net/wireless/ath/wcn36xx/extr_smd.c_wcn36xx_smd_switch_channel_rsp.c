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
struct wcn36xx_hal_switch_channel_rsp_msg {int /*<<< orphan*/  status; int /*<<< orphan*/  channel_number; } ;

/* Variables and functions */
 int /*<<< orphan*/  WCN36XX_DBG_HAL ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wcn36xx_smd_rsp_status_check (void*,size_t) ; 

__attribute__((used)) static int wcn36xx_smd_switch_channel_rsp(void *buf, size_t len)
{
	struct wcn36xx_hal_switch_channel_rsp_msg *rsp;
	int ret;

	ret = wcn36xx_smd_rsp_status_check(buf, len);
	if (ret)
		return ret;
	rsp = (struct wcn36xx_hal_switch_channel_rsp_msg *)buf;
	wcn36xx_dbg(WCN36XX_DBG_HAL, "channel switched to: %d, status: %d\n",
		    rsp->channel_number, rsp->status);
	return ret;
}