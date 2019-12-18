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
struct TYPE_3__ {scalar_t__ sense; } ;
struct scsi_cmnd {void* prot_sdb; scalar_t__ sense_buffer; TYPE_1__ req; int /*<<< orphan*/  flags; } ;
struct scatterlist {int dummy; } ;
struct request {int dummy; } ;
struct blk_mq_tag_set {struct Scsi_Host* driver_data; } ;
struct Scsi_Host {int unchecked_isa_dma; TYPE_2__* hostt; } ;
struct TYPE_4__ {int cmd_size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SCMD_UNCHECKED_ISA_DMA ; 
 struct scsi_cmnd* blk_mq_rq_to_pdu (struct request*) ; 
 scalar_t__ scsi_alloc_sense_buffer (int const,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ scsi_host_get_prot (struct Scsi_Host*) ; 
 int scsi_mq_inline_sgl_size (struct Scsi_Host*) ; 

__attribute__((used)) static int scsi_mq_init_request(struct blk_mq_tag_set *set, struct request *rq,
				unsigned int hctx_idx, unsigned int numa_node)
{
	struct Scsi_Host *shost = set->driver_data;
	const bool unchecked_isa_dma = shost->unchecked_isa_dma;
	struct scsi_cmnd *cmd = blk_mq_rq_to_pdu(rq);
	struct scatterlist *sg;

	if (unchecked_isa_dma)
		cmd->flags |= SCMD_UNCHECKED_ISA_DMA;
	cmd->sense_buffer = scsi_alloc_sense_buffer(unchecked_isa_dma,
						    GFP_KERNEL, numa_node);
	if (!cmd->sense_buffer)
		return -ENOMEM;
	cmd->req.sense = cmd->sense_buffer;

	if (scsi_host_get_prot(shost)) {
		sg = (void *)cmd + sizeof(struct scsi_cmnd) +
			shost->hostt->cmd_size;
		cmd->prot_sdb = (void *)sg + scsi_mq_inline_sgl_size(shost);
	}

	return 0;
}