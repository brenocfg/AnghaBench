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
typedef  int /*<<< orphan*/  u32 ;
struct rvt_mmap_info {scalar_t__ offset; int /*<<< orphan*/  ref; void* obj; struct ib_ucontext* context; int /*<<< orphan*/  size; int /*<<< orphan*/  pending_mmaps; } ;
struct TYPE_2__ {int /*<<< orphan*/  node; } ;
struct rvt_dev_info {scalar_t__ mmap_offset; int /*<<< orphan*/  mmap_offset_lock; TYPE_1__ dparms; } ;
struct ib_ucontext {int dummy; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SHMLBA ; 
 struct rvt_mmap_info* kmalloc_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

struct rvt_mmap_info *rvt_create_mmap_info(struct rvt_dev_info *rdi,
					   u32 size,
					   struct ib_ucontext *context,
					   void *obj)
{
	struct rvt_mmap_info *ip;

	ip = kmalloc_node(sizeof(*ip), GFP_KERNEL, rdi->dparms.node);
	if (!ip)
		return ip;

	size = PAGE_ALIGN(size);

	spin_lock_irq(&rdi->mmap_offset_lock);
	if (rdi->mmap_offset == 0)
		rdi->mmap_offset = ALIGN(PAGE_SIZE, SHMLBA);
	ip->offset = rdi->mmap_offset;
	rdi->mmap_offset += ALIGN(size, SHMLBA);
	spin_unlock_irq(&rdi->mmap_offset_lock);

	INIT_LIST_HEAD(&ip->pending_mmaps);
	ip->size = size;
	ip->context = context;
	ip->obj = obj;
	kref_init(&ip->ref);

	return ip;
}