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
struct pqi_ctrl_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PQI_POST_RESET_DELAY_B4_MSGU_READY ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int pqi_ctrl_init_resume (struct pqi_ctrl_info*) ; 

__attribute__((used)) static int pqi_ofa_ctrl_restart(struct pqi_ctrl_info *ctrl_info)
{
	msleep(PQI_POST_RESET_DELAY_B4_MSGU_READY);
	return pqi_ctrl_init_resume(ctrl_info);
}