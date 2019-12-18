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
 int PWRAP_GET_WACS_RDATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PWRAP_WACS2_CMD ; 
 int /*<<< orphan*/  PWRAP_WACS2_RDATA ; 
 int /*<<< orphan*/  PWRAP_WACS2_VLDCLR ; 
 int /*<<< orphan*/  pwrap_is_fsm_idle ; 
 int /*<<< orphan*/  pwrap_is_fsm_vldclr ; 
 int /*<<< orphan*/  pwrap_leave_fsm_vldclr (struct pmic_wrapper*) ; 
 int /*<<< orphan*/  pwrap_readl (struct pmic_wrapper*,int /*<<< orphan*/ ) ; 
 int pwrap_wait_for_state (struct pmic_wrapper*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrap_writel (struct pmic_wrapper*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pwrap_read16(struct pmic_wrapper *wrp, u32 adr, u32 *rdata)
{
	int ret;

	ret = pwrap_wait_for_state(wrp, pwrap_is_fsm_idle);
	if (ret) {
		pwrap_leave_fsm_vldclr(wrp);
		return ret;
	}

	pwrap_writel(wrp, (adr >> 1) << 16, PWRAP_WACS2_CMD);

	ret = pwrap_wait_for_state(wrp, pwrap_is_fsm_vldclr);
	if (ret)
		return ret;

	*rdata = PWRAP_GET_WACS_RDATA(pwrap_readl(wrp, PWRAP_WACS2_RDATA));

	pwrap_writel(wrp, 1, PWRAP_WACS2_VLDCLR);

	return 0;
}