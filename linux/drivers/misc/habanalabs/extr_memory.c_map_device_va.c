#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct hl_vm_phys_pg_pack {int flags; scalar_t__ asid; int /*<<< orphan*/  mapping_cnt; scalar_t__ total_size; scalar_t__ offset; } ;
struct hl_vm_hash_node {int* ptr; int /*<<< orphan*/  node; scalar_t__ vaddr; } ;
struct hl_vm {int /*<<< orphan*/  idr_lock; int /*<<< orphan*/  phys_pg_pack_handles; } ;
struct hl_userptr {int dummy; } ;
struct TYPE_5__ {scalar_t__ hint_addr; int /*<<< orphan*/  handle; } ;
struct TYPE_4__ {scalar_t__ hint_addr; int /*<<< orphan*/  host_virt_addr; } ;
struct hl_mem_in {int flags; TYPE_2__ map_device; TYPE_1__ map_host; } ;
struct hl_device {int /*<<< orphan*/  dev; TYPE_3__* asic_funcs; struct hl_vm vm; } ;
struct hl_ctx {scalar_t__ asid; int /*<<< orphan*/  dram_va_range; int /*<<< orphan*/  host_va_range; int /*<<< orphan*/  mem_hash_lock; int /*<<< orphan*/  mem_hash; int /*<<< orphan*/  mmu_lock; struct hl_device* hdev; } ;
typedef  enum vm_type_t { ____Placeholder_vm_type_t } vm_type_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* mmu_invalidate_cache ) (struct hl_device*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HL_MEM_SHARED ; 
 int HL_MEM_USERPTR ; 
 scalar_t__ add_va_block (struct hl_device*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free_phys_pg_pack (struct hl_device*,struct hl_vm_phys_pg_pack*) ; 
 int /*<<< orphan*/  free_userptr (struct hl_device*,struct hl_userptr*) ; 
 int get_userptr_from_host_va (struct hl_device*,struct hl_mem_in*,struct hl_userptr**) ; 
 scalar_t__ get_va_block (struct hl_device*,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 struct hl_vm_phys_pg_pack* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int init_phys_pg_pack_from_userptr (struct hl_ctx*,struct hl_userptr*,struct hl_vm_phys_pg_pack**) ; 
 int /*<<< orphan*/  kfree (struct hl_vm_hash_node*) ; 
 struct hl_vm_hash_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int map_phys_page_pack (struct hl_ctx*,scalar_t__,struct hl_vm_phys_pg_pack*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct hl_device*,int) ; 

__attribute__((used)) static int map_device_va(struct hl_ctx *ctx, struct hl_mem_in *args,
		u64 *device_addr)
{
	struct hl_device *hdev = ctx->hdev;
	struct hl_vm *vm = &hdev->vm;
	struct hl_vm_phys_pg_pack *phys_pg_pack;
	struct hl_userptr *userptr = NULL;
	struct hl_vm_hash_node *hnode;
	enum vm_type_t *vm_type;
	u64 ret_vaddr, hint_addr;
	u32 handle = 0;
	int rc;
	bool is_userptr = args->flags & HL_MEM_USERPTR;

	/* Assume failure */
	*device_addr = 0;

	if (is_userptr) {
		rc = get_userptr_from_host_va(hdev, args, &userptr);
		if (rc) {
			dev_err(hdev->dev, "failed to get userptr from va\n");
			return rc;
		}

		rc = init_phys_pg_pack_from_userptr(ctx, userptr,
				&phys_pg_pack);
		if (rc) {
			dev_err(hdev->dev,
				"unable to init page pack for vaddr 0x%llx\n",
				args->map_host.host_virt_addr);
			goto init_page_pack_err;
		}

		vm_type = (enum vm_type_t *) userptr;
		hint_addr = args->map_host.hint_addr;
	} else {
		handle = lower_32_bits(args->map_device.handle);

		spin_lock(&vm->idr_lock);
		phys_pg_pack = idr_find(&vm->phys_pg_pack_handles, handle);
		if (!phys_pg_pack) {
			spin_unlock(&vm->idr_lock);
			dev_err(hdev->dev,
				"no match for handle %u\n", handle);
			return -EINVAL;
		}

		/* increment now to avoid freeing device memory while mapping */
		atomic_inc(&phys_pg_pack->mapping_cnt);

		spin_unlock(&vm->idr_lock);

		vm_type = (enum vm_type_t *) phys_pg_pack;

		hint_addr = args->map_device.hint_addr;
	}

	/*
	 * relevant for mapping device physical memory only, as host memory is
	 * implicitly shared
	 */
	if (!is_userptr && !(phys_pg_pack->flags & HL_MEM_SHARED) &&
			phys_pg_pack->asid != ctx->asid) {
		dev_err(hdev->dev,
			"Failed to map memory, handle %u is not shared\n",
			handle);
		rc = -EPERM;
		goto shared_err;
	}

	hnode = kzalloc(sizeof(*hnode), GFP_KERNEL);
	if (!hnode) {
		rc = -ENOMEM;
		goto hnode_err;
	}

	ret_vaddr = get_va_block(hdev,
			is_userptr ? &ctx->host_va_range : &ctx->dram_va_range,
			phys_pg_pack->total_size, hint_addr, is_userptr);
	if (!ret_vaddr) {
		dev_err(hdev->dev, "no available va block for handle %u\n",
				handle);
		rc = -ENOMEM;
		goto va_block_err;
	}

	mutex_lock(&ctx->mmu_lock);

	rc = map_phys_page_pack(ctx, ret_vaddr, phys_pg_pack);
	if (rc) {
		mutex_unlock(&ctx->mmu_lock);
		dev_err(hdev->dev, "mapping page pack failed for handle %u\n",
				handle);
		goto map_err;
	}

	hdev->asic_funcs->mmu_invalidate_cache(hdev, false);

	mutex_unlock(&ctx->mmu_lock);

	ret_vaddr += phys_pg_pack->offset;

	hnode->ptr = vm_type;
	hnode->vaddr = ret_vaddr;

	mutex_lock(&ctx->mem_hash_lock);
	hash_add(ctx->mem_hash, &hnode->node, ret_vaddr);
	mutex_unlock(&ctx->mem_hash_lock);

	*device_addr = ret_vaddr;

	if (is_userptr)
		free_phys_pg_pack(hdev, phys_pg_pack);

	return 0;

map_err:
	if (add_va_block(hdev,
			is_userptr ? &ctx->host_va_range : &ctx->dram_va_range,
			ret_vaddr,
			ret_vaddr + phys_pg_pack->total_size - 1))
		dev_warn(hdev->dev,
			"release va block failed for handle 0x%x, vaddr: 0x%llx\n",
				handle, ret_vaddr);

va_block_err:
	kfree(hnode);
hnode_err:
shared_err:
	atomic_dec(&phys_pg_pack->mapping_cnt);
	if (is_userptr)
		free_phys_pg_pack(hdev, phys_pg_pack);
init_page_pack_err:
	if (is_userptr)
		free_userptr(hdev, userptr);

	return rc;
}