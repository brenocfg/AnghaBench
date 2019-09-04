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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct pp_hwmgr {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgs_write_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmSMC_MSG_ARG_0 ; 
 int smu7_send_msg_to_smc_without_waiting (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

int smu7_send_msg_to_smc_with_parameter_without_waiting(struct pp_hwmgr *hwmgr, uint16_t msg, uint32_t parameter)
{
	cgs_write_register(hwmgr->device, mmSMC_MSG_ARG_0, parameter);

	return smu7_send_msg_to_smc_without_waiting(hwmgr, msg);
}