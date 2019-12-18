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
typedef  int /*<<< orphan*/  u8 ;
struct iommu_cmd {int dummy; } ;
struct amd_iommu {int cmd_buf_tail; scalar_t__ mmio_base; int /*<<< orphan*/ * cmd_buf; } ;

/* Variables and functions */
 int CMD_BUFFER_SIZE ; 
 scalar_t__ MMIO_CMD_TAIL_OFFSET ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct iommu_cmd*,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void copy_cmd_to_buffer(struct amd_iommu *iommu,
			       struct iommu_cmd *cmd)
{
	u8 *target;

	target = iommu->cmd_buf + iommu->cmd_buf_tail;

	iommu->cmd_buf_tail += sizeof(*cmd);
	iommu->cmd_buf_tail %= CMD_BUFFER_SIZE;

	/* Copy command to buffer */
	memcpy(target, cmd, sizeof(*cmd));

	/* Tell the IOMMU about it */
	writel(iommu->cmd_buf_tail, iommu->mmio_base + MMIO_CMD_TAIL_OFFSET);
}