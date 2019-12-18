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
struct hl_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRAM_PHYS_BASE ; 
 int /*<<< orphan*/  HOST_PHYS_BASE ; 
 int /*<<< orphan*/  HOST_PHYS_SIZE ; 
 int /*<<< orphan*/  SRAM_BASE_ADDR ; 
 int hl_pci_init_iatu (struct hl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int goya_init_iatu(struct hl_device *hdev)
{
	return hl_pci_init_iatu(hdev, SRAM_BASE_ADDR, DRAM_PHYS_BASE,
				HOST_PHYS_BASE, HOST_PHYS_SIZE);
}