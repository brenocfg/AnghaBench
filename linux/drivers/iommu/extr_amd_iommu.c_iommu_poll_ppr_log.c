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
typedef  unsigned long u64 ;
typedef  int u32 ;
struct amd_iommu {scalar_t__ mmio_base; int /*<<< orphan*/ * ppr_log; } ;

/* Variables and functions */
 int LOOP_TIMEOUT ; 
 scalar_t__ MMIO_PPR_HEAD_OFFSET ; 
 scalar_t__ MMIO_PPR_TAIL_OFFSET ; 
 int PPR_ENTRY_SIZE ; 
 int PPR_LOG_SIZE ; 
 scalar_t__ PPR_REQ_TYPE (unsigned long volatile) ; 
 int /*<<< orphan*/  iommu_handle_ppr_entry (struct amd_iommu*,unsigned long*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void iommu_poll_ppr_log(struct amd_iommu *iommu)
{
	u32 head, tail;

	if (iommu->ppr_log == NULL)
		return;

	head = readl(iommu->mmio_base + MMIO_PPR_HEAD_OFFSET);
	tail = readl(iommu->mmio_base + MMIO_PPR_TAIL_OFFSET);

	while (head != tail) {
		volatile u64 *raw;
		u64 entry[2];
		int i;

		raw = (u64 *)(iommu->ppr_log + head);

		/*
		 * Hardware bug: Interrupt may arrive before the entry is
		 * written to memory. If this happens we need to wait for the
		 * entry to arrive.
		 */
		for (i = 0; i < LOOP_TIMEOUT; ++i) {
			if (PPR_REQ_TYPE(raw[0]) != 0)
				break;
			udelay(1);
		}

		/* Avoid memcpy function-call overhead */
		entry[0] = raw[0];
		entry[1] = raw[1];

		/*
		 * To detect the hardware bug we need to clear the entry
		 * back to zero.
		 */
		raw[0] = raw[1] = 0UL;

		/* Update head pointer of hardware ring-buffer */
		head = (head + PPR_ENTRY_SIZE) % PPR_LOG_SIZE;
		writel(head, iommu->mmio_base + MMIO_PPR_HEAD_OFFSET);

		/* Handle PPR entry */
		iommu_handle_ppr_entry(iommu, entry);

		/* Refresh ring-buffer information */
		head = readl(iommu->mmio_base + MMIO_PPR_HEAD_OFFSET);
		tail = readl(iommu->mmio_base + MMIO_PPR_TAIL_OFFSET);
	}
}