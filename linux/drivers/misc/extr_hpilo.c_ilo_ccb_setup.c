#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ilo_hwinfo {int /*<<< orphan*/ * db_vaddr; int /*<<< orphan*/  ilo_dev; } ;
struct TYPE_10__ {int /*<<< orphan*/ * db_base; } ;
struct TYPE_9__ {char* recv_desc; unsigned long recv_desc_pa; } ;
struct TYPE_8__ {char* send_desc; unsigned long send_desc_pa; } ;
struct TYPE_7__ {char* recv_fifobar; int recv_fifobar_pa; } ;
struct TYPE_6__ {char* send_fifobar; int send_fifobar_pa; } ;
struct ccb {int channel; TYPE_5__ ccb_u5; TYPE_4__ ccb_u4; TYPE_3__ ccb_u2; TYPE_2__ ccb_u3; TYPE_1__ ccb_u1; } ;
struct ccb_data {unsigned long dma_pa; scalar_t__ dma_size; scalar_t__ dma_va; struct ccb ilo_ccb; struct ccb driver_ccb; } ;
typedef  unsigned long dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int FIFOHANDLESIZE ; 
 scalar_t__ ILO_CACHE_SZ ; 
 scalar_t__ ILO_START_ALIGN ; 
 int L2_DB_SIZE ; 
 int /*<<< orphan*/  L2_QENTRY_SZ ; 
 int /*<<< orphan*/  NR_QENTRY ; 
 int /*<<< orphan*/  ctrl_setup (struct ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long desc_mem_sz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fifo_setup (char*,int /*<<< orphan*/ ) ; 
 unsigned long fifo_sz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ pci_alloc_consistent (int /*<<< orphan*/ ,scalar_t__,unsigned long*) ; 
 unsigned long roundup (unsigned long,scalar_t__) ; 

__attribute__((used)) static int ilo_ccb_setup(struct ilo_hwinfo *hw, struct ccb_data *data, int slot)
{
	char *dma_va;
	dma_addr_t dma_pa;
	struct ccb *driver_ccb, *ilo_ccb;

	driver_ccb = &data->driver_ccb;
	ilo_ccb = &data->ilo_ccb;

	data->dma_size = 2 * fifo_sz(NR_QENTRY) +
			 2 * desc_mem_sz(NR_QENTRY) +
			 ILO_START_ALIGN + ILO_CACHE_SZ;

	data->dma_va = pci_alloc_consistent(hw->ilo_dev, data->dma_size,
					    &data->dma_pa);
	if (!data->dma_va)
		return -ENOMEM;

	dma_va = (char *)data->dma_va;
	dma_pa = data->dma_pa;

	memset(dma_va, 0, data->dma_size);

	dma_va = (char *)roundup((unsigned long)dma_va, ILO_START_ALIGN);
	dma_pa = roundup(dma_pa, ILO_START_ALIGN);

	/*
	 * Create two ccb's, one with virt addrs, one with phys addrs.
	 * Copy the phys addr ccb to device shared mem.
	 */
	ctrl_setup(driver_ccb, NR_QENTRY, L2_QENTRY_SZ);
	ctrl_setup(ilo_ccb, NR_QENTRY, L2_QENTRY_SZ);

	fifo_setup(dma_va, NR_QENTRY);
	driver_ccb->ccb_u1.send_fifobar = dma_va + FIFOHANDLESIZE;
	ilo_ccb->ccb_u1.send_fifobar_pa = dma_pa + FIFOHANDLESIZE;
	dma_va += fifo_sz(NR_QENTRY);
	dma_pa += fifo_sz(NR_QENTRY);

	dma_va = (char *)roundup((unsigned long)dma_va, ILO_CACHE_SZ);
	dma_pa = roundup(dma_pa, ILO_CACHE_SZ);

	fifo_setup(dma_va, NR_QENTRY);
	driver_ccb->ccb_u3.recv_fifobar = dma_va + FIFOHANDLESIZE;
	ilo_ccb->ccb_u3.recv_fifobar_pa = dma_pa + FIFOHANDLESIZE;
	dma_va += fifo_sz(NR_QENTRY);
	dma_pa += fifo_sz(NR_QENTRY);

	driver_ccb->ccb_u2.send_desc = dma_va;
	ilo_ccb->ccb_u2.send_desc_pa = dma_pa;
	dma_pa += desc_mem_sz(NR_QENTRY);
	dma_va += desc_mem_sz(NR_QENTRY);

	driver_ccb->ccb_u4.recv_desc = dma_va;
	ilo_ccb->ccb_u4.recv_desc_pa = dma_pa;

	driver_ccb->channel = slot;
	ilo_ccb->channel = slot;

	driver_ccb->ccb_u5.db_base = hw->db_vaddr + (slot << L2_DB_SIZE);
	ilo_ccb->ccb_u5.db_base = NULL; /* hw ccb's doorbell is not used */

	return 0;
}