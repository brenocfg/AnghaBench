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
struct dpages {unsigned long vma_invalidate_size; int /*<<< orphan*/ * vma_invalidate_address; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; int /*<<< orphan*/ * vma; int /*<<< orphan*/  bio; int /*<<< orphan*/  pl; } ;
struct TYPE_4__ {int type; TYPE_1__ ptr; int /*<<< orphan*/  offset; } ;
struct dm_io_request {TYPE_2__ mem; int /*<<< orphan*/  bi_op; } ;

/* Variables and functions */
#define  DM_IO_BIO 131 
#define  DM_IO_KMEM 130 
#define  DM_IO_PAGE_LIST 129 
#define  DM_IO_VMA 128 
 int EINVAL ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  bio_dp_init (struct dpages*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_kernel_vmap_range (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  km_dp_init (struct dpages*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_dp_init (struct dpages*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_dp_init (struct dpages*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dp_init(struct dm_io_request *io_req, struct dpages *dp,
		   unsigned long size)
{
	/* Set up dpages based on memory type */

	dp->vma_invalidate_address = NULL;
	dp->vma_invalidate_size = 0;

	switch (io_req->mem.type) {
	case DM_IO_PAGE_LIST:
		list_dp_init(dp, io_req->mem.ptr.pl, io_req->mem.offset);
		break;

	case DM_IO_BIO:
		bio_dp_init(dp, io_req->mem.ptr.bio);
		break;

	case DM_IO_VMA:
		flush_kernel_vmap_range(io_req->mem.ptr.vma, size);
		if (io_req->bi_op == REQ_OP_READ) {
			dp->vma_invalidate_address = io_req->mem.ptr.vma;
			dp->vma_invalidate_size = size;
		}
		vm_dp_init(dp, io_req->mem.ptr.vma);
		break;

	case DM_IO_KMEM:
		km_dp_init(dp, io_req->mem.ptr.addr);
		break;

	default:
		return -EINVAL;
	}

	return 0;
}