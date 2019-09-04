#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct threshold_block {unsigned int block; unsigned int bank; unsigned int cpu; int address; int interrupt_enable; int /*<<< orphan*/  miscj; int /*<<< orphan*/  kobj; scalar_t__ interrupt_capable; int /*<<< orphan*/  threshold_limit; } ;
struct TYPE_9__ {int /*<<< orphan*/  attr; } ;
struct TYPE_8__ {unsigned int banks; } ;
struct TYPE_7__ {int /*<<< orphan*/  kobj; struct threshold_block* blocks; } ;
struct TYPE_6__ {int /*<<< orphan*/ ** default_attrs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int MASK_CNTP_HI ; 
 int MASK_LOCKED_HI ; 
 int MASK_VALID_HI ; 
 unsigned int NR_BLOCKS ; 
 int /*<<< orphan*/  THRESHOLD_MAX ; 
 int get_block_address (int,int,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  get_name (unsigned int,struct threshold_block*) ; 
 TYPE_5__ interrupt_enable ; 
 int /*<<< orphan*/  kfree (struct threshold_block*) ; 
 int kobject_init_and_add (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct threshold_block* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ lvt_interrupt_supported (unsigned int,int) ; 
 TYPE_3__ mca_cfg ; 
 TYPE_2__** per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ rdmsr_safe_on_cpu (unsigned int,int,int*,int*) ; 
 int /*<<< orphan*/  threshold_banks ; 
 TYPE_1__ threshold_ktype ; 

__attribute__((used)) static int allocate_threshold_blocks(unsigned int cpu, unsigned int bank,
				     unsigned int block, u32 address)
{
	struct threshold_block *b = NULL;
	u32 low, high;
	int err;

	if ((bank >= mca_cfg.banks) || (block >= NR_BLOCKS))
		return 0;

	if (rdmsr_safe_on_cpu(cpu, address, &low, &high))
		return 0;

	if (!(high & MASK_VALID_HI)) {
		if (block)
			goto recurse;
		else
			return 0;
	}

	if (!(high & MASK_CNTP_HI)  ||
	     (high & MASK_LOCKED_HI))
		goto recurse;

	b = kzalloc(sizeof(struct threshold_block), GFP_KERNEL);
	if (!b)
		return -ENOMEM;

	b->block		= block;
	b->bank			= bank;
	b->cpu			= cpu;
	b->address		= address;
	b->interrupt_enable	= 0;
	b->interrupt_capable	= lvt_interrupt_supported(bank, high);
	b->threshold_limit	= THRESHOLD_MAX;

	if (b->interrupt_capable) {
		threshold_ktype.default_attrs[2] = &interrupt_enable.attr;
		b->interrupt_enable = 1;
	} else {
		threshold_ktype.default_attrs[2] = NULL;
	}

	INIT_LIST_HEAD(&b->miscj);

	if (per_cpu(threshold_banks, cpu)[bank]->blocks) {
		list_add(&b->miscj,
			 &per_cpu(threshold_banks, cpu)[bank]->blocks->miscj);
	} else {
		per_cpu(threshold_banks, cpu)[bank]->blocks = b;
	}

	err = kobject_init_and_add(&b->kobj, &threshold_ktype,
				   per_cpu(threshold_banks, cpu)[bank]->kobj,
				   get_name(bank, b));
	if (err)
		goto out_free;
recurse:
	address = get_block_address(address, low, high, bank, ++block);
	if (!address)
		return 0;

	err = allocate_threshold_blocks(cpu, bank, block, address);
	if (err)
		goto out_free;

	if (b)
		kobject_uevent(&b->kobj, KOBJ_ADD);

	return err;

out_free:
	if (b) {
		kobject_put(&b->kobj);
		list_del(&b->miscj);
		kfree(b);
	}
	return err;
}