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
struct pp_hwmgr {int /*<<< orphan*/ * device; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgs_read_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmSMU_MP1_SRBM2P_ARG_0 ; 

__attribute__((used)) static uint32_t smu8_get_argument(struct pp_hwmgr *hwmgr)
{
	if (hwmgr == NULL || hwmgr->device == NULL)
		return 0;

	return cgs_read_register(hwmgr->device,
					mmSMU_MP1_SRBM2P_ARG_0);
}