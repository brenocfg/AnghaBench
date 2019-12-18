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
typedef  int u32 ;
struct panfrost_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  AS_FAULTADDRESS_HI (int) ; 
 int /*<<< orphan*/  AS_FAULTADDRESS_LO (int) ; 
 int /*<<< orphan*/  AS_FAULTSTATUS (int) ; 
 int BIT (int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MMU_INT_CLEAR ; 
 int /*<<< orphan*/  MMU_INT_MASK ; 
 int /*<<< orphan*/  MMU_INT_RAWSTAT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  access_type_name (struct panfrost_device*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int,char*,int,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int mmu_read (struct panfrost_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_write (struct panfrost_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panfrost_exception_name (struct panfrost_device*,int) ; 
 int panfrost_mmu_map_fault_addr (struct panfrost_device*,int,int) ; 

__attribute__((used)) static irqreturn_t panfrost_mmu_irq_handler_thread(int irq, void *data)
{
	struct panfrost_device *pfdev = data;
	u32 status = mmu_read(pfdev, MMU_INT_RAWSTAT);
	int i, ret;

	for (i = 0; status; i++) {
		u32 mask = BIT(i) | BIT(i + 16);
		u64 addr;
		u32 fault_status;
		u32 exception_type;
		u32 access_type;
		u32 source_id;

		if (!(status & mask))
			continue;

		fault_status = mmu_read(pfdev, AS_FAULTSTATUS(i));
		addr = mmu_read(pfdev, AS_FAULTADDRESS_LO(i));
		addr |= (u64)mmu_read(pfdev, AS_FAULTADDRESS_HI(i)) << 32;

		/* decode the fault status */
		exception_type = fault_status & 0xFF;
		access_type = (fault_status >> 8) & 0x3;
		source_id = (fault_status >> 16);

		/* Page fault only */
		if ((status & mask) == BIT(i)) {
			WARN_ON(exception_type < 0xC1 || exception_type > 0xC4);

			ret = panfrost_mmu_map_fault_addr(pfdev, i, addr);
			if (!ret) {
				mmu_write(pfdev, MMU_INT_CLEAR, BIT(i));
				status &= ~mask;
				continue;
			}
		}

		/* terminal fault, print info about the fault */
		dev_err(pfdev->dev,
			"Unhandled Page fault in AS%d at VA 0x%016llX\n"
			"Reason: %s\n"
			"raw fault status: 0x%X\n"
			"decoded fault status: %s\n"
			"exception type 0x%X: %s\n"
			"access type 0x%X: %s\n"
			"source id 0x%X\n",
			i, addr,
			"TODO",
			fault_status,
			(fault_status & (1 << 10) ? "DECODER FAULT" : "SLAVE FAULT"),
			exception_type, panfrost_exception_name(pfdev, exception_type),
			access_type, access_type_name(pfdev, fault_status),
			source_id);

		mmu_write(pfdev, MMU_INT_CLEAR, mask);

		status &= ~mask;
	}

	mmu_write(pfdev, MMU_INT_MASK, ~0);
	return IRQ_HANDLED;
}