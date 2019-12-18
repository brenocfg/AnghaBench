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
struct iss_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  ISP5_CTRL ; 
 int ISP5_CTRL_MSTANDBY ; 
 int ISP5_CTRL_MSTANDBY_WAIT ; 
 int /*<<< orphan*/  ISP5_SYSCONFIG ; 
 int ISP5_SYSCONFIG_SOFTRESET ; 
 int /*<<< orphan*/  ISP5_SYSCONFIG_STANDBYMODE_MASK ; 
 int /*<<< orphan*/  ISP5_SYSCONFIG_STANDBYMODE_SMART ; 
 int /*<<< orphan*/  OMAP4_ISS_MEM_ISP_SYS1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int iss_poll_condition_timeout (int,int,int,int) ; 
 int iss_reg_read (struct iss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iss_reg_set (struct iss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iss_reg_update (struct iss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iss_isp_reset(struct iss_device *iss)
{
	unsigned int timeout;

	/* Fist, ensure that the ISP is IDLE (no transactions happening) */
	iss_reg_update(iss, OMAP4_ISS_MEM_ISP_SYS1, ISP5_SYSCONFIG,
		       ISP5_SYSCONFIG_STANDBYMODE_MASK,
		       ISP5_SYSCONFIG_STANDBYMODE_SMART);

	iss_reg_set(iss, OMAP4_ISS_MEM_ISP_SYS1, ISP5_CTRL, ISP5_CTRL_MSTANDBY);

	timeout = iss_poll_condition_timeout(
		iss_reg_read(iss, OMAP4_ISS_MEM_ISP_SYS1, ISP5_CTRL) &
		ISP5_CTRL_MSTANDBY_WAIT, 1000000, 1000, 1500);
	if (timeout) {
		dev_err(iss->dev, "ISP5 standby timeout\n");
		return -ETIMEDOUT;
	}

	/* Now finally, do the reset */
	iss_reg_set(iss, OMAP4_ISS_MEM_ISP_SYS1, ISP5_SYSCONFIG,
		    ISP5_SYSCONFIG_SOFTRESET);

	timeout = iss_poll_condition_timeout(
		!(iss_reg_read(iss, OMAP4_ISS_MEM_ISP_SYS1, ISP5_SYSCONFIG) &
		ISP5_SYSCONFIG_SOFTRESET), 1000000, 1000, 1500);
	if (timeout) {
		dev_err(iss->dev, "ISP5 reset timeout\n");
		return -ETIMEDOUT;
	}

	return 0;
}