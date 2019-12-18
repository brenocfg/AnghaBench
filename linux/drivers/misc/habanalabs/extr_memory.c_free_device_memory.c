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
typedef  int /*<<< orphan*/  u32 ;
struct hl_vm_phys_pg_pack {int /*<<< orphan*/  total_size; int /*<<< orphan*/  mapping_cnt; } ;
struct hl_vm {int /*<<< orphan*/  idr_lock; int /*<<< orphan*/  phys_pg_pack_handles; } ;
struct hl_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  dram_used_mem; struct hl_vm vm; } ;
struct hl_ctx {int /*<<< orphan*/  dram_phys_mem; struct hl_device* hdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  atomic64_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_phys_pg_pack (struct hl_device*,struct hl_vm_phys_pg_pack*) ; 
 struct hl_vm_phys_pg_pack* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int free_device_memory(struct hl_ctx *ctx, u32 handle)
{
	struct hl_device *hdev = ctx->hdev;
	struct hl_vm *vm = &hdev->vm;
	struct hl_vm_phys_pg_pack *phys_pg_pack;

	spin_lock(&vm->idr_lock);
	phys_pg_pack = idr_find(&vm->phys_pg_pack_handles, handle);
	if (phys_pg_pack) {
		if (atomic_read(&phys_pg_pack->mapping_cnt) > 0) {
			dev_err(hdev->dev, "handle %u is mapped, cannot free\n",
				handle);
			spin_unlock(&vm->idr_lock);
			return -EINVAL;
		}

		/*
		 * must remove from idr before the freeing of the physical
		 * pages as the refcount of the pool is also the trigger of the
		 * idr destroy
		 */
		idr_remove(&vm->phys_pg_pack_handles, handle);
		spin_unlock(&vm->idr_lock);

		atomic64_sub(phys_pg_pack->total_size, &ctx->dram_phys_mem);
		atomic64_sub(phys_pg_pack->total_size, &hdev->dram_used_mem);

		free_phys_pg_pack(hdev, phys_pg_pack);
	} else {
		spin_unlock(&vm->idr_lock);
		dev_err(hdev->dev,
			"free device memory failed, no match for handle %u\n",
			handle);
		return -EINVAL;
	}

	return 0;
}