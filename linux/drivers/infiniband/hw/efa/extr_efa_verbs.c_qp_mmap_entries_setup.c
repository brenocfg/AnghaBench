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
struct efa_ucontext {int dummy; } ;
struct efa_qp {scalar_t__ rq_size; int /*<<< orphan*/  rq_cpu_addr; } ;
struct efa_ibv_create_qp_resp {scalar_t__ sq_db_mmap_key; int sq_db_offset; scalar_t__ llq_desc_mmap_key; int llq_desc_offset; scalar_t__ rq_db_mmap_key; int rq_db_offset; scalar_t__ rq_mmap_key; scalar_t__ rq_mmap_size; } ;
struct efa_dev {scalar_t__ db_bar_addr; scalar_t__ mem_bar_addr; } ;
struct efa_com_create_qp_params {scalar_t__ sq_ring_size_in_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFA_MMAP_DMA_PAGE ; 
 scalar_t__ EFA_MMAP_INVALID ; 
 int /*<<< orphan*/  EFA_MMAP_IO_NC ; 
 int /*<<< orphan*/  EFA_MMAP_IO_WC ; 
 int ENOMEM ; 
 scalar_t__ PAGE_ALIGN (scalar_t__) ; 
 int PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 void* mmap_entry_insert (struct efa_dev*,struct efa_ucontext*,struct efa_qp*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ virt_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qp_mmap_entries_setup(struct efa_qp *qp,
				 struct efa_dev *dev,
				 struct efa_ucontext *ucontext,
				 struct efa_com_create_qp_params *params,
				 struct efa_ibv_create_qp_resp *resp)
{
	/*
	 * Once an entry is inserted it might be mmapped, hence cannot be
	 * cleaned up until dealloc_ucontext.
	 */
	resp->sq_db_mmap_key =
		mmap_entry_insert(dev, ucontext, qp,
				  dev->db_bar_addr + resp->sq_db_offset,
				  PAGE_SIZE, EFA_MMAP_IO_NC);
	if (resp->sq_db_mmap_key == EFA_MMAP_INVALID)
		return -ENOMEM;

	resp->sq_db_offset &= ~PAGE_MASK;

	resp->llq_desc_mmap_key =
		mmap_entry_insert(dev, ucontext, qp,
				  dev->mem_bar_addr + resp->llq_desc_offset,
				  PAGE_ALIGN(params->sq_ring_size_in_bytes +
					     (resp->llq_desc_offset & ~PAGE_MASK)),
				  EFA_MMAP_IO_WC);
	if (resp->llq_desc_mmap_key == EFA_MMAP_INVALID)
		return -ENOMEM;

	resp->llq_desc_offset &= ~PAGE_MASK;

	if (qp->rq_size) {
		resp->rq_db_mmap_key =
			mmap_entry_insert(dev, ucontext, qp,
					  dev->db_bar_addr + resp->rq_db_offset,
					  PAGE_SIZE, EFA_MMAP_IO_NC);
		if (resp->rq_db_mmap_key == EFA_MMAP_INVALID)
			return -ENOMEM;

		resp->rq_db_offset &= ~PAGE_MASK;

		resp->rq_mmap_key =
			mmap_entry_insert(dev, ucontext, qp,
					  virt_to_phys(qp->rq_cpu_addr),
					  qp->rq_size, EFA_MMAP_DMA_PAGE);
		if (resp->rq_mmap_key == EFA_MMAP_INVALID)
			return -ENOMEM;

		resp->rq_mmap_size = qp->rq_size;
	}

	return 0;
}