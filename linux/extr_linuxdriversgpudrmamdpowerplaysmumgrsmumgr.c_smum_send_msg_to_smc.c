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
typedef  int /*<<< orphan*/  uint16_t ;
struct pp_hwmgr {TYPE_1__* smumgr_funcs; } ;
struct TYPE_2__ {int (* send_msg_to_smc ) (struct pp_hwmgr*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

int smum_send_msg_to_smc(struct pp_hwmgr *hwmgr, uint16_t msg)
{
	if (hwmgr == NULL || hwmgr->smumgr_funcs->send_msg_to_smc == NULL)
		return -EINVAL;

	return hwmgr->smumgr_funcs->send_msg_to_smc(hwmgr, msg);
}