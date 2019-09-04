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
struct nes_vnic {struct nes_device* nesdev; } ;
struct nes_qp_context {int dummy; } ;
struct TYPE_2__ {void* q2_vbase; scalar_t__ q2_pbase; scalar_t__ rq_pbase; scalar_t__ sq_pbase; void* rq_vbase; void* sq_vbase; } ;
struct nes_qp {int qp_mem_size; void* nesqp_context; TYPE_1__ hwqp; scalar_t__ nesqp_context_pbase; } ;
struct nes_hw_qp_wqe {int dummy; } ;
struct nes_device {int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NES_DBG_QP ; 
 int PAGE_SIZE ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,void*,unsigned long,int) ; 
 void* pci_alloc_consistent (int /*<<< orphan*/ ,int,scalar_t__*) ; 

__attribute__((used)) static int nes_setup_mmap_qp(struct nes_qp *nesqp, struct nes_vnic *nesvnic,
		int sq_size, int rq_size)
{
	void *mem;
	struct nes_device *nesdev = nesvnic->nesdev;

	nesqp->qp_mem_size = (sizeof(struct nes_hw_qp_wqe) * sq_size) +
			(sizeof(struct nes_hw_qp_wqe) * rq_size) +
			max((u32)sizeof(struct nes_qp_context), ((u32)256)) +
			256; /* this is Q2 */
	/* Round up to a multiple of a page */
	nesqp->qp_mem_size += PAGE_SIZE - 1;
	nesqp->qp_mem_size &= ~(PAGE_SIZE - 1);

	mem = pci_alloc_consistent(nesdev->pcidev, nesqp->qp_mem_size,
			&nesqp->hwqp.sq_pbase);
	if (!mem)
		return -ENOMEM;
	nes_debug(NES_DBG_QP, "PCI consistent memory for "
			"host descriptor rings located @ %p (pa = 0x%08lX.) size = %u.\n",
			mem, (unsigned long)nesqp->hwqp.sq_pbase, nesqp->qp_mem_size);

	memset(mem, 0, nesqp->qp_mem_size);

	nesqp->hwqp.sq_vbase = mem;
	mem += sizeof(struct nes_hw_qp_wqe) * sq_size;

	nesqp->hwqp.rq_vbase = mem;
	nesqp->hwqp.rq_pbase = nesqp->hwqp.sq_pbase +
			sizeof(struct nes_hw_qp_wqe) * sq_size;
	mem += sizeof(struct nes_hw_qp_wqe) * rq_size;

	nesqp->hwqp.q2_vbase = mem;
	nesqp->hwqp.q2_pbase = nesqp->hwqp.rq_pbase +
			sizeof(struct nes_hw_qp_wqe) * rq_size;
	mem += 256;
	memset(nesqp->hwqp.q2_vbase, 0, 256);

	nesqp->nesqp_context = mem;
	nesqp->nesqp_context_pbase = nesqp->hwqp.q2_pbase + 256;
	memset(nesqp->nesqp_context, 0, sizeof(*nesqp->nesqp_context));
	return 0;
}