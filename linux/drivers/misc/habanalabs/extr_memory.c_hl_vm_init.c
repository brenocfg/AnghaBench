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
struct hl_vm {int init_done; int /*<<< orphan*/  dram_pg_pool; int /*<<< orphan*/  phys_pg_pack_handles; int /*<<< orphan*/  idr_lock; int /*<<< orphan*/  dram_pg_pool_refcount; } ;
struct asic_fixed_properties {scalar_t__ dram_user_base_address; scalar_t__ dram_end_address; int /*<<< orphan*/  dram_page_size; } ;
struct hl_device {int /*<<< orphan*/  dram_used_mem; int /*<<< orphan*/  dev; struct hl_vm vm; struct asic_fixed_properties asic_prop; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  __ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int gen_pool_add (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  gen_pool_create (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int hl_vm_init(struct hl_device *hdev)
{
	struct asic_fixed_properties *prop = &hdev->asic_prop;
	struct hl_vm *vm = &hdev->vm;
	int rc;

	vm->dram_pg_pool = gen_pool_create(__ffs(prop->dram_page_size), -1);
	if (!vm->dram_pg_pool) {
		dev_err(hdev->dev, "Failed to create dram page pool\n");
		return -ENOMEM;
	}

	kref_init(&vm->dram_pg_pool_refcount);

	rc = gen_pool_add(vm->dram_pg_pool, prop->dram_user_base_address,
			prop->dram_end_address - prop->dram_user_base_address,
			-1);

	if (rc) {
		dev_err(hdev->dev,
			"Failed to add memory to dram page pool %d\n", rc);
		goto pool_add_err;
	}

	spin_lock_init(&vm->idr_lock);
	idr_init(&vm->phys_pg_pack_handles);

	atomic64_set(&hdev->dram_used_mem, 0);

	vm->init_done = true;

	return 0;

pool_add_err:
	gen_pool_destroy(vm->dram_pg_pool);

	return rc;
}