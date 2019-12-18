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
struct iommu_cmd {int* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_COMPL_WAIT ; 
 int CMD_COMPL_WAIT_STORE_MASK ; 
 int /*<<< orphan*/  CMD_SET_TYPE (struct iommu_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int iommu_virt_to_phys (void*) ; 
 int lower_32_bits (int) ; 
 int /*<<< orphan*/  memset (struct iommu_cmd*,int /*<<< orphan*/ ,int) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void build_completion_wait(struct iommu_cmd *cmd, u64 address)
{
	u64 paddr = iommu_virt_to_phys((void *)address);

	WARN_ON(address & 0x7ULL);

	memset(cmd, 0, sizeof(*cmd));
	cmd->data[0] = lower_32_bits(paddr) | CMD_COMPL_WAIT_STORE_MASK;
	cmd->data[1] = upper_32_bits(paddr);
	cmd->data[2] = 1;
	CMD_SET_TYPE(cmd, CMD_COMPL_WAIT);
}