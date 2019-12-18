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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct hl_vm_phys_pg_pack {int /*<<< orphan*/ * pages; } ;
struct hl_vm {int /*<<< orphan*/  idr_lock; int /*<<< orphan*/  phys_pg_pack_handles; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;
struct hl_mem_in {TYPE_1__ map_device; } ;
struct hl_device {int /*<<< orphan*/  dev; struct hl_vm vm; } ;
struct hl_ctx {struct hl_device* hdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct hl_vm_phys_pg_pack* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_paddr_from_handle(struct hl_ctx *ctx, struct hl_mem_in *args,
				u64 *paddr)
{
	struct hl_device *hdev = ctx->hdev;
	struct hl_vm *vm = &hdev->vm;
	struct hl_vm_phys_pg_pack *phys_pg_pack;
	u32 handle;

	handle = lower_32_bits(args->map_device.handle);
	spin_lock(&vm->idr_lock);
	phys_pg_pack = idr_find(&vm->phys_pg_pack_handles, handle);
	if (!phys_pg_pack) {
		spin_unlock(&vm->idr_lock);
		dev_err(hdev->dev, "no match for handle %u\n", handle);
		return -EINVAL;
	}

	*paddr = phys_pg_pack->pages[0];

	spin_unlock(&vm->idr_lock);

	return 0;
}