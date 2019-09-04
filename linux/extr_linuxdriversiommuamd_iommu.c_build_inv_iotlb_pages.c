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
typedef  int u64 ;
typedef  void* u16 ;
struct iommu_cmd {int* data; } ;

/* Variables and functions */
 int CMD_INV_IOMMU_ALL_PAGES_ADDRESS ; 
 int CMD_INV_IOMMU_PAGES_SIZE_MASK ; 
 int /*<<< orphan*/  CMD_INV_IOTLB_PAGES ; 
 int /*<<< orphan*/  CMD_SET_TYPE (struct iommu_cmd*,int /*<<< orphan*/ ) ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int iommu_num_pages (int,size_t,int /*<<< orphan*/ ) ; 
 int lower_32_bits (int) ; 
 int /*<<< orphan*/  memset (struct iommu_cmd*,int /*<<< orphan*/ ,int) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void build_inv_iotlb_pages(struct iommu_cmd *cmd, u16 devid, int qdep,
				  u64 address, size_t size)
{
	u64 pages;
	bool s;

	pages = iommu_num_pages(address, size, PAGE_SIZE);
	s     = false;

	if (pages > 1) {
		/*
		 * If we have to flush more than one page, flush all
		 * TLB entries for this domain
		 */
		address = CMD_INV_IOMMU_ALL_PAGES_ADDRESS;
		s = true;
	}

	address &= PAGE_MASK;

	memset(cmd, 0, sizeof(*cmd));
	cmd->data[0]  = devid;
	cmd->data[0] |= (qdep & 0xff) << 24;
	cmd->data[1]  = devid;
	cmd->data[2]  = lower_32_bits(address);
	cmd->data[3]  = upper_32_bits(address);
	CMD_SET_TYPE(cmd, CMD_INV_IOTLB_PAGES);
	if (s)
		cmd->data[2] |= CMD_INV_IOMMU_PAGES_SIZE_MASK;
}