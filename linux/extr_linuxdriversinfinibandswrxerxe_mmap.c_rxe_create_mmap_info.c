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
struct TYPE_2__ {scalar_t__ offset; int /*<<< orphan*/  size; } ;
struct rxe_mmap_info {int /*<<< orphan*/  ref; void* obj; struct ib_ucontext* context; TYPE_1__ info; int /*<<< orphan*/  pending_mmaps; } ;
struct rxe_dev {scalar_t__ mmap_offset; int /*<<< orphan*/  mmap_offset_lock; } ;
struct ib_ucontext {int dummy; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SHMLBA ; 
 struct rxe_mmap_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

struct rxe_mmap_info *rxe_create_mmap_info(struct rxe_dev *rxe,
					   u32 size,
					   struct ib_ucontext *context,
					   void *obj)
{
	struct rxe_mmap_info *ip;

	ip = kmalloc(sizeof(*ip), GFP_KERNEL);
	if (!ip)
		return NULL;

	size = PAGE_ALIGN(size);

	spin_lock_bh(&rxe->mmap_offset_lock);

	if (rxe->mmap_offset == 0)
		rxe->mmap_offset = ALIGN(PAGE_SIZE, SHMLBA);

	ip->info.offset = rxe->mmap_offset;
	rxe->mmap_offset += ALIGN(size, SHMLBA);

	spin_unlock_bh(&rxe->mmap_offset_lock);

	INIT_LIST_HEAD(&ip->pending_mmaps);
	ip->info.size = size;
	ip->context = context;
	ip->obj = obj;
	kref_init(&ip->ref);

	return ip;
}