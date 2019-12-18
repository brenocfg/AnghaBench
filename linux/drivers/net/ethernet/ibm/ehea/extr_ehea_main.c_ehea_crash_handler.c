#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int num_entries; TYPE_1__* arr; } ;
struct TYPE_7__ {int num_entries; TYPE_2__* arr; } ;
struct TYPE_6__ {int /*<<< orphan*/  fwh; int /*<<< orphan*/  adh; } ;
struct TYPE_5__ {int /*<<< orphan*/  macaddr; int /*<<< orphan*/  reg_type; int /*<<< orphan*/  port_id; int /*<<< orphan*/  adh; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORCE_FREE ; 
 int /*<<< orphan*/  H_DEREG_BCMC ; 
 TYPE_4__ ehea_bcmc_regs ; 
 TYPE_3__ ehea_fw_handles ; 
 int /*<<< orphan*/  ehea_h_free_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehea_h_reg_dereg_bcmc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ehea_crash_handler(void)
{
	int i;

	if (ehea_fw_handles.arr)
		for (i = 0; i < ehea_fw_handles.num_entries; i++)
			ehea_h_free_resource(ehea_fw_handles.arr[i].adh,
					     ehea_fw_handles.arr[i].fwh,
					     FORCE_FREE);

	if (ehea_bcmc_regs.arr)
		for (i = 0; i < ehea_bcmc_regs.num_entries; i++)
			ehea_h_reg_dereg_bcmc(ehea_bcmc_regs.arr[i].adh,
					      ehea_bcmc_regs.arr[i].port_id,
					      ehea_bcmc_regs.arr[i].reg_type,
					      ehea_bcmc_regs.arr[i].macaddr,
					      0, H_DEREG_BCMC);
}