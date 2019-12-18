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
struct pmic_wrapper {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWRAP_WACS2_VLDCLR ; 
 scalar_t__ pwrap_is_fsm_vldclr (struct pmic_wrapper*) ; 
 int /*<<< orphan*/  pwrap_writel (struct pmic_wrapper*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void pwrap_leave_fsm_vldclr(struct pmic_wrapper *wrp)
{
	if (pwrap_is_fsm_vldclr(wrp))
		pwrap_writel(wrp, 1, PWRAP_WACS2_VLDCLR);
}