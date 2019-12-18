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
struct rtc_time {int dummy; } ;
struct imx_sc_rpc_msg {int size; int /*<<< orphan*/  func; int /*<<< orphan*/  svc; int /*<<< orphan*/  ver; } ;
struct imx_sc_msg_timer_get_rtc_time {int /*<<< orphan*/  time; struct imx_sc_rpc_msg hdr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX_SC_RPC_SVC_TIMER ; 
 int /*<<< orphan*/  IMX_SC_RPC_VERSION ; 
 int /*<<< orphan*/  IMX_SC_TIMER_FUNC_GET_RTC_SEC1970 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int imx_scu_call_rpc (int /*<<< orphan*/ ,struct imx_sc_msg_timer_get_rtc_time*,int) ; 
 int /*<<< orphan*/  rtc_ipc_handle ; 
 int /*<<< orphan*/  rtc_time64_to_tm (int /*<<< orphan*/ ,struct rtc_time*) ; 

__attribute__((used)) static int imx_sc_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct imx_sc_msg_timer_get_rtc_time msg;
	struct imx_sc_rpc_msg *hdr = &msg.hdr;
	int ret;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_TIMER;
	hdr->func = IMX_SC_TIMER_FUNC_GET_RTC_SEC1970;
	hdr->size = 1;

	ret = imx_scu_call_rpc(rtc_ipc_handle, &msg, true);
	if (ret) {
		dev_err(dev, "read rtc time failed, ret %d\n", ret);
		return ret;
	}

	rtc_time64_to_tm(msg.time, tm);

	return 0;
}