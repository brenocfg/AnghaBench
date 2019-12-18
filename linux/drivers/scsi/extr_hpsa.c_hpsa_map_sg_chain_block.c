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
typedef  int u32 ;
struct ctlr_info {int max_cmd_sg_entries; TYPE_2__* pdev; struct SGDescriptor** cmd_sg_list; } ;
struct SGDescriptor {void* Addr; void* Len; void* Ext; } ;
struct TYPE_3__ {int /*<<< orphan*/  SGTotal; } ;
struct CommandList {size_t cmdindex; TYPE_1__ Header; struct SGDescriptor* SG; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int HPSA_SG_CHAIN ; 
 void* cpu_to_le32 (int) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,struct SGDescriptor*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpsa_map_sg_chain_block(struct ctlr_info *h,
	struct CommandList *c)
{
	struct SGDescriptor *chain_sg, *chain_block;
	u64 temp64;
	u32 chain_len;

	chain_sg = &c->SG[h->max_cmd_sg_entries - 1];
	chain_block = h->cmd_sg_list[c->cmdindex];
	chain_sg->Ext = cpu_to_le32(HPSA_SG_CHAIN);
	chain_len = sizeof(*chain_sg) *
		(le16_to_cpu(c->Header.SGTotal) - h->max_cmd_sg_entries);
	chain_sg->Len = cpu_to_le32(chain_len);
	temp64 = dma_map_single(&h->pdev->dev, chain_block, chain_len,
				DMA_TO_DEVICE);
	if (dma_mapping_error(&h->pdev->dev, temp64)) {
		/* prevent subsequent unmapping */
		chain_sg->Addr = cpu_to_le64(0);
		return -1;
	}
	chain_sg->Addr = cpu_to_le64(temp64);
	return 0;
}