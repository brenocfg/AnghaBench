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
struct slgt_info {int reg_addr_requested; int /*<<< orphan*/  init_error; int /*<<< orphan*/  phys_reg_addr; int /*<<< orphan*/  device_name; int /*<<< orphan*/  reg_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGERR (char*) ; 
 int /*<<< orphan*/  DiagStatus_AddressConflict ; 
 int /*<<< orphan*/  DiagStatus_CantAssignPciResources ; 
 int ENODEV ; 
 int /*<<< orphan*/  SLGT_REG_SIZE ; 
 int /*<<< orphan*/  ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_resources (struct slgt_info*) ; 
 int /*<<< orphan*/ * request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int claim_resources(struct slgt_info *info)
{
	if (request_mem_region(info->phys_reg_addr, SLGT_REG_SIZE, "synclink_gt") == NULL) {
		DBGERR(("%s reg addr conflict, addr=%08X\n",
			info->device_name, info->phys_reg_addr));
		info->init_error = DiagStatus_AddressConflict;
		goto errout;
	}
	else
		info->reg_addr_requested = true;

	info->reg_addr = ioremap_nocache(info->phys_reg_addr, SLGT_REG_SIZE);
	if (!info->reg_addr) {
		DBGERR(("%s can't map device registers, addr=%08X\n",
			info->device_name, info->phys_reg_addr));
		info->init_error = DiagStatus_CantAssignPciResources;
		goto errout;
	}
	return 0;

errout:
	release_resources(info);
	return -ENODEV;
}