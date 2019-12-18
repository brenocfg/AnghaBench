#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct seq_file {struct hl_debugfs_entry* private; } ;
struct hl_device {int /*<<< orphan*/  dev; TYPE_1__* asic_funcs; struct hl_ctx* compute_ctx; struct hl_ctx* kernel_ctx; int /*<<< orphan*/  mmu_enable; } ;
struct hl_debugfs_entry {struct hl_dbg_device_entry* dev_entry; } ;
struct hl_dbg_device_entry {scalar_t__ mmu_addr; scalar_t__ mmu_asid; struct hl_device* hdev; } ;
struct hl_ctx {int /*<<< orphan*/  mmu_lock; } ;
struct TYPE_2__ {scalar_t__ (* read_pte ) (struct hl_device*,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ HL_KERNEL_ASID_ID ; 
 scalar_t__ LAST_MASK ; 
 scalar_t__ PAGE_PRESENT_MASK ; 
 scalar_t__ ULLONG_MAX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ get_hop0_addr (struct hl_ctx*) ; 
 scalar_t__ get_hop0_pte_addr (struct hl_ctx*,scalar_t__,scalar_t__) ; 
 scalar_t__ get_hop1_pte_addr (struct hl_ctx*,scalar_t__,scalar_t__) ; 
 scalar_t__ get_hop2_pte_addr (struct hl_ctx*,scalar_t__,scalar_t__) ; 
 scalar_t__ get_hop3_pte_addr (struct hl_ctx*,scalar_t__,scalar_t__) ; 
 scalar_t__ get_hop4_pte_addr (struct hl_ctx*,scalar_t__,scalar_t__) ; 
 scalar_t__ get_next_hop_addr (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__,...) ; 
 scalar_t__ stub1 (struct hl_device*,scalar_t__) ; 
 scalar_t__ stub2 (struct hl_device*,scalar_t__) ; 
 scalar_t__ stub3 (struct hl_device*,scalar_t__) ; 
 scalar_t__ stub4 (struct hl_device*,scalar_t__) ; 
 scalar_t__ stub5 (struct hl_device*,scalar_t__) ; 

__attribute__((used)) static int mmu_show(struct seq_file *s, void *data)
{
	struct hl_debugfs_entry *entry = s->private;
	struct hl_dbg_device_entry *dev_entry = entry->dev_entry;
	struct hl_device *hdev = dev_entry->hdev;
	struct hl_ctx *ctx;

	u64 hop0_addr = 0, hop0_pte_addr = 0, hop0_pte = 0,
		hop1_addr = 0, hop1_pte_addr = 0, hop1_pte = 0,
		hop2_addr = 0, hop2_pte_addr = 0, hop2_pte = 0,
		hop3_addr = 0, hop3_pte_addr = 0, hop3_pte = 0,
		hop4_addr = 0, hop4_pte_addr = 0, hop4_pte = 0,
		virt_addr = dev_entry->mmu_addr;

	if (!hdev->mmu_enable)
		return 0;

	if (dev_entry->mmu_asid == HL_KERNEL_ASID_ID)
		ctx = hdev->kernel_ctx;
	else
		ctx = hdev->compute_ctx;

	if (!ctx) {
		dev_err(hdev->dev, "no ctx available\n");
		return 0;
	}

	mutex_lock(&ctx->mmu_lock);

	/* the following lookup is copied from unmap() in mmu.c */

	hop0_addr = get_hop0_addr(ctx);
	hop0_pte_addr = get_hop0_pte_addr(ctx, hop0_addr, virt_addr);
	hop0_pte = hdev->asic_funcs->read_pte(hdev, hop0_pte_addr);
	hop1_addr = get_next_hop_addr(hop0_pte);

	if (hop1_addr == ULLONG_MAX)
		goto not_mapped;

	hop1_pte_addr = get_hop1_pte_addr(ctx, hop1_addr, virt_addr);
	hop1_pte = hdev->asic_funcs->read_pte(hdev, hop1_pte_addr);
	hop2_addr = get_next_hop_addr(hop1_pte);

	if (hop2_addr == ULLONG_MAX)
		goto not_mapped;

	hop2_pte_addr = get_hop2_pte_addr(ctx, hop2_addr, virt_addr);
	hop2_pte = hdev->asic_funcs->read_pte(hdev, hop2_pte_addr);
	hop3_addr = get_next_hop_addr(hop2_pte);

	if (hop3_addr == ULLONG_MAX)
		goto not_mapped;

	hop3_pte_addr = get_hop3_pte_addr(ctx, hop3_addr, virt_addr);
	hop3_pte = hdev->asic_funcs->read_pte(hdev, hop3_pte_addr);

	if (!(hop3_pte & LAST_MASK)) {
		hop4_addr = get_next_hop_addr(hop3_pte);

		if (hop4_addr == ULLONG_MAX)
			goto not_mapped;

		hop4_pte_addr = get_hop4_pte_addr(ctx, hop4_addr, virt_addr);
		hop4_pte = hdev->asic_funcs->read_pte(hdev, hop4_pte_addr);
		if (!(hop4_pte & PAGE_PRESENT_MASK))
			goto not_mapped;
	} else {
		if (!(hop3_pte & PAGE_PRESENT_MASK))
			goto not_mapped;
	}

	seq_printf(s, "asid: %u, virt_addr: 0x%llx\n",
			dev_entry->mmu_asid, dev_entry->mmu_addr);

	seq_printf(s, "hop0_addr: 0x%llx\n", hop0_addr);
	seq_printf(s, "hop0_pte_addr: 0x%llx\n", hop0_pte_addr);
	seq_printf(s, "hop0_pte: 0x%llx\n", hop0_pte);

	seq_printf(s, "hop1_addr: 0x%llx\n", hop1_addr);
	seq_printf(s, "hop1_pte_addr: 0x%llx\n", hop1_pte_addr);
	seq_printf(s, "hop1_pte: 0x%llx\n", hop1_pte);

	seq_printf(s, "hop2_addr: 0x%llx\n", hop2_addr);
	seq_printf(s, "hop2_pte_addr: 0x%llx\n", hop2_pte_addr);
	seq_printf(s, "hop2_pte: 0x%llx\n", hop2_pte);

	seq_printf(s, "hop3_addr: 0x%llx\n", hop3_addr);
	seq_printf(s, "hop3_pte_addr: 0x%llx\n", hop3_pte_addr);
	seq_printf(s, "hop3_pte: 0x%llx\n", hop3_pte);

	if (!(hop3_pte & LAST_MASK)) {
		seq_printf(s, "hop4_addr: 0x%llx\n", hop4_addr);
		seq_printf(s, "hop4_pte_addr: 0x%llx\n", hop4_pte_addr);
		seq_printf(s, "hop4_pte: 0x%llx\n", hop4_pte);
	}

	goto out;

not_mapped:
	dev_err(hdev->dev, "virt addr 0x%llx is not mapped to phys addr\n",
			virt_addr);
out:
	mutex_unlock(&ctx->mmu_lock);

	return 0;
}