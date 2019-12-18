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
 int CMD_INV_IOMMU_PAGES_GN_MASK ; 
 int CMD_INV_IOMMU_PAGES_SIZE_MASK ; 
 int /*<<< orphan*/  CMD_INV_IOTLB_PAGES ; 
 int /*<<< orphan*/  CMD_SET_TYPE (struct iommu_cmd*,int /*<<< orphan*/ ) ; 
 int lower_32_bits (int) ; 
 int /*<<< orphan*/  memset (struct iommu_cmd*,int /*<<< orphan*/ ,int) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void build_inv_iotlb_pasid(struct iommu_cmd *cmd, u16 devid, int pasid,
				  int qdep, u64 address, bool size)
{
	memset(cmd, 0, sizeof(*cmd));

	address &= ~(0xfffULL);

	cmd->data[0]  = devid;
	cmd->data[0] |= ((pasid >> 8) & 0xff) << 16;
	cmd->data[0] |= (qdep  & 0xff) << 24;
	cmd->data[1]  = devid;
	cmd->data[1] |= (pasid & 0xff) << 16;
	cmd->data[2]  = lower_32_bits(address);
	cmd->data[2] |= CMD_INV_IOMMU_PAGES_GN_MASK;
	cmd->data[3]  = upper_32_bits(address);
	if (size)
		cmd->data[2] |= CMD_INV_IOMMU_PAGES_SIZE_MASK;
	CMD_SET_TYPE(cmd, CMD_INV_IOTLB_PAGES);
}