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
typedef  int /*<<< orphan*/  u16 ;
struct flexcop_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMM_PID ; 
 int /*<<< orphan*/  EMM_filter_sig ; 
 int /*<<< orphan*/  EMM_trans ; 
 int /*<<< orphan*/  pid_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pid_filter_308 ; 

__attribute__((used)) static void flexcop_pid_EMM_PID_ctrl(struct flexcop_device *fc,
		u16 pid, int onoff)
{
	pid_ctrl(pid_filter_308, EMM_PID, EMM_filter_sig, EMM_trans, 0);
}