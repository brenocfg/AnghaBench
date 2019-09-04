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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct amd_iommu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static u32 iommu_read_l1(struct amd_iommu *iommu, u16 l1, u8 address)
{
	u32 val;

	pci_write_config_dword(iommu->dev, 0xf8, (address | l1 << 16));
	pci_read_config_dword(iommu->dev, 0xfc, &val);
	return val;
}