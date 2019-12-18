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
struct scatterlist {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; int /*<<< orphan*/  lkey; } ;
struct iser_mem_reg {TYPE_2__ sge; scalar_t__ rkey; } ;
struct iser_device {TYPE_1__* pd; } ;
struct iser_data_buf {struct scatterlist* sg; } ;
struct TYPE_3__ {int flags; scalar_t__ unsafe_global_rkey; int /*<<< orphan*/  local_dma_lkey; } ;

/* Variables and functions */
 int IB_PD_UNSAFE_GLOBAL_RKEY ; 
 int /*<<< orphan*/  iser_dbg (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_dma_address (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_dma_len (struct scatterlist*) ; 

__attribute__((used)) static int
iser_reg_dma(struct iser_device *device, struct iser_data_buf *mem,
	     struct iser_mem_reg *reg)
{
	struct scatterlist *sg = mem->sg;

	reg->sge.lkey = device->pd->local_dma_lkey;
	/*
	 * FIXME: rework the registration code path to differentiate
	 * rkey/lkey use cases
	 */

	if (device->pd->flags & IB_PD_UNSAFE_GLOBAL_RKEY)
		reg->rkey = device->pd->unsafe_global_rkey;
	else
		reg->rkey = 0;
	reg->sge.addr = sg_dma_address(&sg[0]);
	reg->sge.length = sg_dma_len(&sg[0]);

	iser_dbg("Single DMA entry: lkey=0x%x, rkey=0x%x, addr=0x%llx,"
		 " length=0x%x\n", reg->sge.lkey, reg->rkey,
		 reg->sge.addr, reg->sge.length);

	return 0;
}