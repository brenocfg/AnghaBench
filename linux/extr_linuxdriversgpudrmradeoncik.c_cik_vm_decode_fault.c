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
typedef  int u32 ;
struct radeon_device {scalar_t__ family; } ;

/* Variables and functions */
 scalar_t__ CHIP_HAWAII ; 
 int FAULT_VMID_MASK ; 
 int FAULT_VMID_SHIFT ; 
 int HAWAII_MEMORY_CLIENT_ID_MASK ; 
 int MEMORY_CLIENT_ID_MASK ; 
 int MEMORY_CLIENT_ID_SHIFT ; 
 int MEMORY_CLIENT_RW_MASK ; 
 int PROTECTIONS_MASK ; 
 int PROTECTIONS_SHIFT ; 
 int /*<<< orphan*/  printk (char*,int,int,int,char*,char*,int,int) ; 

__attribute__((used)) static void cik_vm_decode_fault(struct radeon_device *rdev,
				u32 status, u32 addr, u32 mc_client)
{
	u32 mc_id;
	u32 vmid = (status & FAULT_VMID_MASK) >> FAULT_VMID_SHIFT;
	u32 protections = (status & PROTECTIONS_MASK) >> PROTECTIONS_SHIFT;
	char block[5] = { mc_client >> 24, (mc_client >> 16) & 0xff,
		(mc_client >> 8) & 0xff, mc_client & 0xff, 0 };

	if (rdev->family == CHIP_HAWAII)
		mc_id = (status & HAWAII_MEMORY_CLIENT_ID_MASK) >> MEMORY_CLIENT_ID_SHIFT;
	else
		mc_id = (status & MEMORY_CLIENT_ID_MASK) >> MEMORY_CLIENT_ID_SHIFT;

	printk("VM fault (0x%02x, vmid %d) at page %u, %s from '%s' (0x%08x) (%d)\n",
	       protections, vmid, addr,
	       (status & MEMORY_CLIENT_RW_MASK) ? "write" : "read",
	       block, mc_client, mc_id);
}