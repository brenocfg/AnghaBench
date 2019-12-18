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
struct TYPE_2__ {int /*<<< orphan*/  MC; } ;
struct pp_hwmgr {int /*<<< orphan*/  device; TYPE_1__ microcode_version_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgs_read_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgs_write_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmMC_SEQ_IO_DEBUG_DATA ; 
 int /*<<< orphan*/  mmMC_SEQ_IO_DEBUG_INDEX ; 

__attribute__((used)) static int smu7_get_mc_microcode_version(struct pp_hwmgr *hwmgr)
{
	cgs_write_register(hwmgr->device, mmMC_SEQ_IO_DEBUG_INDEX, 0x9F);

	hwmgr->microcode_version_info.MC = cgs_read_register(hwmgr->device, mmMC_SEQ_IO_DEBUG_DATA);

	return 0;
}