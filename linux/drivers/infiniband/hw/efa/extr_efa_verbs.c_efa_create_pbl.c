#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* chunks; } ;
struct TYPE_12__ {TYPE_3__ chunk_list; } ;
struct TYPE_9__ {int /*<<< orphan*/  dma_addr; } ;
struct TYPE_13__ {TYPE_4__ indirect; TYPE_1__ continuous; } ;
struct pbl_context {TYPE_5__ phys; int /*<<< orphan*/  pbl_buf_size_in_bytes; scalar_t__ physically_continuous; } ;
struct efa_mr {int /*<<< orphan*/  umem; } ;
struct efa_dev {int /*<<< orphan*/  ibdev; } ;
struct TYPE_14__ {int /*<<< orphan*/  mem_addr_low; int /*<<< orphan*/  mem_addr_high; } ;
struct TYPE_15__ {TYPE_6__ address; int /*<<< orphan*/  length; } ;
struct TYPE_16__ {TYPE_7__ pbl; } ;
struct efa_com_reg_mr_params {int indirect; TYPE_8__ pbl; scalar_t__ inline_pbl; int /*<<< orphan*/  page_shift; int /*<<< orphan*/  page_num; } ;
struct TYPE_10__ {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  efa_com_set_dma_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibdev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int pbl_create (struct efa_dev*,struct pbl_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efa_create_pbl(struct efa_dev *dev,
			  struct pbl_context *pbl,
			  struct efa_mr *mr,
			  struct efa_com_reg_mr_params *params)
{
	int err;

	err = pbl_create(dev, pbl, mr->umem, params->page_num,
			 params->page_shift);
	if (err) {
		ibdev_dbg(&dev->ibdev, "Failed to create pbl[%d]\n", err);
		return err;
	}

	params->inline_pbl = 0;
	params->indirect = !pbl->physically_continuous;
	if (pbl->physically_continuous) {
		params->pbl.pbl.length = pbl->pbl_buf_size_in_bytes;

		efa_com_set_dma_addr(pbl->phys.continuous.dma_addr,
				     &params->pbl.pbl.address.mem_addr_high,
				     &params->pbl.pbl.address.mem_addr_low);
	} else {
		params->pbl.pbl.length =
			pbl->phys.indirect.chunk_list.chunks[0].length;

		efa_com_set_dma_addr(pbl->phys.indirect.chunk_list.chunks[0].dma_addr,
				     &params->pbl.pbl.address.mem_addr_high,
				     &params->pbl.pbl.address.mem_addr_low);
	}

	return 0;
}