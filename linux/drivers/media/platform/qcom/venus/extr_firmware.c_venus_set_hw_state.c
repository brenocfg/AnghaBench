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
struct venus_core {scalar_t__ base; scalar_t__ use_tz; } ;

/* Variables and functions */
 scalar_t__ WRAPPER_A9SS_SW_RESET ; 
 int qcom_scm_set_remote_state (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  venus_reset_cpu (struct venus_core*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int venus_set_hw_state(struct venus_core *core, bool resume)
{
	if (core->use_tz)
		return qcom_scm_set_remote_state(resume, 0);

	if (resume)
		venus_reset_cpu(core);
	else
		writel(1, core->base + WRAPPER_A9SS_SW_RESET);

	return 0;
}