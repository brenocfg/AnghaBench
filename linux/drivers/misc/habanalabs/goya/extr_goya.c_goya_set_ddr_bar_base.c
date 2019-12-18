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
typedef  scalar_t__ u64 ;
struct hl_device {struct goya_device* asic_specific; } ;
struct goya_device {scalar_t__ ddr_bar_cur_addr; } ;

/* Variables and functions */
 scalar_t__ U64_MAX ; 
 int hl_pci_set_dram_bar_base (struct hl_device*,int,int,scalar_t__) ; 

__attribute__((used)) static u64 goya_set_ddr_bar_base(struct hl_device *hdev, u64 addr)
{
	struct goya_device *goya = hdev->asic_specific;
	u64 old_addr = addr;
	int rc;

	if ((goya) && (goya->ddr_bar_cur_addr == addr))
		return old_addr;

	/* Inbound Region 1 - Bar 4 - Point to DDR */
	rc = hl_pci_set_dram_bar_base(hdev, 1, 4, addr);
	if (rc)
		return U64_MAX;

	if (goya) {
		old_addr = goya->ddr_bar_cur_addr;
		goya->ddr_bar_cur_addr = addr;
	}

	return old_addr;
}