#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  scalar_t__ u64 ;
struct ntb_msi_desc {int /*<<< orphan*/  data; scalar_t__ addr_offset; } ;
struct ntb_dev {TYPE_1__* msi; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ address_lo; int /*<<< orphan*/  data; scalar_t__ address_hi; } ;
struct msi_desc {TYPE_2__ msg; int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {scalar_t__ base_addr; scalar_t__ end_addr; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  dev_warn_once (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int ntb_msi_set_desc(struct ntb_dev *ntb, struct msi_desc *entry,
			    struct ntb_msi_desc *msi_desc)
{
	u64 addr;

	addr = entry->msg.address_lo +
		((uint64_t)entry->msg.address_hi << 32);

	if (addr < ntb->msi->base_addr || addr >= ntb->msi->end_addr) {
		dev_warn_once(&ntb->dev,
			      "IRQ %d: MSI Address not within the memory window (%llx, [%llx %llx])\n",
			      entry->irq, addr, ntb->msi->base_addr,
			      ntb->msi->end_addr);
		return -EFAULT;
	}

	msi_desc->addr_offset = addr - ntb->msi->base_addr;
	msi_desc->data = entry->msg.data;

	return 0;
}