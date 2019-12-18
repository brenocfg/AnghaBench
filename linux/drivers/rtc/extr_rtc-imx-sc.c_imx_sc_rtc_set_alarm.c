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
struct rtc_time {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
struct rtc_wkalrm {int /*<<< orphan*/  enabled; struct rtc_time time; } ;
struct imx_sc_rpc_msg {int size; int /*<<< orphan*/  func; int /*<<< orphan*/  svc; int /*<<< orphan*/  ver; } ;
struct imx_sc_msg_timer_rtc_set_alarm {int /*<<< orphan*/  sec; int /*<<< orphan*/  min; int /*<<< orphan*/  hour; int /*<<< orphan*/  day; scalar_t__ mon; scalar_t__ year; struct imx_sc_rpc_msg hdr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX_SC_RPC_SVC_TIMER ; 
 int /*<<< orphan*/  IMX_SC_RPC_VERSION ; 
 int /*<<< orphan*/  IMX_SC_TIMER_FUNC_SET_RTC_ALARM ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int imx_sc_rtc_alarm_irq_enable (struct device*,int /*<<< orphan*/ ) ; 
 int imx_scu_call_rpc (int /*<<< orphan*/ ,struct imx_sc_msg_timer_rtc_set_alarm*,int) ; 
 int /*<<< orphan*/  rtc_ipc_handle ; 

__attribute__((used)) static int imx_sc_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct imx_sc_msg_timer_rtc_set_alarm msg;
	struct imx_sc_rpc_msg *hdr = &msg.hdr;
	int ret;
	struct rtc_time *alrm_tm = &alrm->time;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_TIMER;
	hdr->func = IMX_SC_TIMER_FUNC_SET_RTC_ALARM;
	hdr->size = 3;

	msg.year = alrm_tm->tm_year + 1900;
	msg.mon = alrm_tm->tm_mon + 1;
	msg.day = alrm_tm->tm_mday;
	msg.hour = alrm_tm->tm_hour;
	msg.min = alrm_tm->tm_min;
	msg.sec = alrm_tm->tm_sec;

	ret = imx_scu_call_rpc(rtc_ipc_handle, &msg, true);
	if (ret) {
		dev_err(dev, "set rtc alarm failed, ret %d\n", ret);
		return ret;
	}

	ret = imx_sc_rtc_alarm_irq_enable(dev, alrm->enabled);
	if (ret) {
		dev_err(dev, "enable rtc alarm failed, ret %d\n", ret);
		return ret;
	}

	return 0;
}