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
struct rtc_time {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; } ;
struct device {int dummy; } ;
struct arm_smccc_res {int a0; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX_SIP_SRTC ; 
 int /*<<< orphan*/  IMX_SIP_SRTC_SET_TIME ; 
 int /*<<< orphan*/  arm_smccc_smc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arm_smccc_res*) ; 

__attribute__((used)) static int imx_sc_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct arm_smccc_res res;

	/* pack 2 time parameters into 1 register, 16 bits for each */
	arm_smccc_smc(IMX_SIP_SRTC, IMX_SIP_SRTC_SET_TIME,
		      ((tm->tm_year + 1900) << 16) | (tm->tm_mon + 1),
		      (tm->tm_mday << 16) | tm->tm_hour,
		      (tm->tm_min << 16) | tm->tm_sec,
		      0, 0, 0, &res);

	return res.a0;
}