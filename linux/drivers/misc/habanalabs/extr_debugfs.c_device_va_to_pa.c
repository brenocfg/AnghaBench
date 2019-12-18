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
struct hl_device {int /*<<< orphan*/  dev; TYPE_1__* asic_funcs; struct hl_ctx* compute_ctx; } ;
struct hl_ctx {int /*<<< orphan*/  mmu_lock; } ;
struct TYPE_2__ {scalar_t__ (* read_pte ) (struct hl_device*,scalar_t__) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HOP4_MASK ; 
 scalar_t__ LAST_MASK ; 
 scalar_t__ OFFSET_MASK ; 
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
 scalar_t__ stub1 (struct hl_device*,scalar_t__) ; 
 scalar_t__ stub2 (struct hl_device*,scalar_t__) ; 
 scalar_t__ stub3 (struct hl_device*,scalar_t__) ; 
 scalar_t__ stub4 (struct hl_device*,scalar_t__) ; 
 scalar_t__ stub5 (struct hl_device*,scalar_t__) ; 

__attribute__((used)) static int device_va_to_pa(struct hl_device *hdev, u64 virt_addr,
				u64 *phys_addr)
{
	struct hl_ctx *ctx = hdev->compute_ctx;
	u64 hop_addr, hop_pte_addr, hop_pte;
	u64 offset_mask = HOP4_MASK | OFFSET_MASK;
	int rc = 0;

	if (!ctx) {
		dev_err(hdev->dev, "no ctx available\n");
		return -EINVAL;
	}

	mutex_lock(&ctx->mmu_lock);

	/* hop 0 */
	hop_addr = get_hop0_addr(ctx);
	hop_pte_addr = get_hop0_pte_addr(ctx, hop_addr, virt_addr);
	hop_pte = hdev->asic_funcs->read_pte(hdev, hop_pte_addr);

	/* hop 1 */
	hop_addr = get_next_hop_addr(hop_pte);
	if (hop_addr == ULLONG_MAX)
		goto not_mapped;
	hop_pte_addr = get_hop1_pte_addr(ctx, hop_addr, virt_addr);
	hop_pte = hdev->asic_funcs->read_pte(hdev, hop_pte_addr);

	/* hop 2 */
	hop_addr = get_next_hop_addr(hop_pte);
	if (hop_addr == ULLONG_MAX)
		goto not_mapped;
	hop_pte_addr = get_hop2_pte_addr(ctx, hop_addr, virt_addr);
	hop_pte = hdev->asic_funcs->read_pte(hdev, hop_pte_addr);

	/* hop 3 */
	hop_addr = get_next_hop_addr(hop_pte);
	if (hop_addr == ULLONG_MAX)
		goto not_mapped;
	hop_pte_addr = get_hop3_pte_addr(ctx, hop_addr, virt_addr);
	hop_pte = hdev->asic_funcs->read_pte(hdev, hop_pte_addr);

	if (!(hop_pte & LAST_MASK)) {
		/* hop 4 */
		hop_addr = get_next_hop_addr(hop_pte);
		if (hop_addr == ULLONG_MAX)
			goto not_mapped;
		hop_pte_addr = get_hop4_pte_addr(ctx, hop_addr, virt_addr);
		hop_pte = hdev->asic_funcs->read_pte(hdev, hop_pte_addr);

		offset_mask = OFFSET_MASK;
	}

	if (!(hop_pte & PAGE_PRESENT_MASK))
		goto not_mapped;

	*phys_addr = (hop_pte & ~offset_mask) | (virt_addr & offset_mask);

	goto out;

not_mapped:
	dev_err(hdev->dev, "virt addr 0x%llx is not mapped to phys addr\n",
			virt_addr);
	rc = -EINVAL;
out:
	mutex_unlock(&ctx->mmu_lock);
	return rc;
}