#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pqi_ctrl_info {TYPE_1__* registers; } ;
struct TYPE_2__ {int /*<<< orphan*/  sis_host_to_ctrl_doorbell; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIS_SOFT_RESET ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void sis_soft_reset(struct pqi_ctrl_info *ctrl_info)
{
	writel(SIS_SOFT_RESET,
		&ctrl_info->registers->sis_host_to_ctrl_doorbell);
}