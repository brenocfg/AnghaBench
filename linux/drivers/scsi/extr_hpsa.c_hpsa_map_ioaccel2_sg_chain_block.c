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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ioaccel2_sg_element {int dummy; } ;
struct io_accel2_cmd {TYPE_2__* sg; } ;
struct ctlr_info {TYPE_1__* pdev; struct ioaccel2_sg_element** ioaccel2_cmd_sg_list; } ;
struct CommandList {size_t cmdindex; } ;
struct TYPE_4__ {int /*<<< orphan*/  address; int /*<<< orphan*/  length; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,struct ioaccel2_sg_element*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpsa_map_ioaccel2_sg_chain_block(struct ctlr_info *h,
	struct io_accel2_cmd *cp, struct CommandList *c)
{
	struct ioaccel2_sg_element *chain_block;
	u64 temp64;
	u32 chain_size;

	chain_block = h->ioaccel2_cmd_sg_list[c->cmdindex];
	chain_size = le32_to_cpu(cp->sg[0].length);
	temp64 = dma_map_single(&h->pdev->dev, chain_block, chain_size,
				DMA_TO_DEVICE);
	if (dma_mapping_error(&h->pdev->dev, temp64)) {
		/* prevent subsequent unmapping */
		cp->sg->address = 0;
		return -1;
	}
	cp->sg->address = cpu_to_le64(temp64);
	return 0;
}