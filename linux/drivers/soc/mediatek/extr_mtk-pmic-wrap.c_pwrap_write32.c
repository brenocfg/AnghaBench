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
typedef  int u32 ;
struct pmic_wrapper {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWRAP_WACS2_CMD ; 
 int /*<<< orphan*/  pwrap_is_fsm_idle ; 
 int /*<<< orphan*/  pwrap_leave_fsm_vldclr (struct pmic_wrapper*) ; 
 int /*<<< orphan*/  pwrap_read (struct pmic_wrapper*,int,int*) ; 
 int pwrap_wait_for_state (struct pmic_wrapper*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrap_writel (struct pmic_wrapper*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pwrap_write32(struct pmic_wrapper *wrp, u32 adr, u32 wdata)
{
	int ret, msb, rdata;

	for (msb = 0; msb < 2; msb++) {
		ret = pwrap_wait_for_state(wrp, pwrap_is_fsm_idle);
		if (ret) {
			pwrap_leave_fsm_vldclr(wrp);
			return ret;
		}

		pwrap_writel(wrp, (1 << 31) | (msb << 30) | (adr << 16) |
			     ((wdata >> (msb * 16)) & 0xffff),
			     PWRAP_WACS2_CMD);

		/*
		 * The pwrap_read operation is the requirement of hardware used
		 * for the synchronization between two successive 16-bit
		 * pwrap_writel operations composing one 32-bit bus writing.
		 * Otherwise, we'll find the result fails on the lower 16-bit
		 * pwrap writing.
		 */
		if (!msb)
			pwrap_read(wrp, adr, &rdata);
	}

	return 0;
}