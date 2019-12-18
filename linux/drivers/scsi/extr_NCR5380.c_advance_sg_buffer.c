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
struct TYPE_2__ {struct scatterlist* buffer; scalar_t__ this_residual; int /*<<< orphan*/  ptr; } ;
struct scsi_cmnd {TYPE_1__ SCp; } ;
struct scatterlist {scalar_t__ length; } ;

/* Variables and functions */
 int /*<<< orphan*/  sg_is_last (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_virt (struct scatterlist*) ; 

__attribute__((used)) static inline void advance_sg_buffer(struct scsi_cmnd *cmd)
{
	struct scatterlist *s = cmd->SCp.buffer;

	if (!cmd->SCp.this_residual && s && !sg_is_last(s)) {
		cmd->SCp.buffer = sg_next(s);
		cmd->SCp.ptr = sg_virt(cmd->SCp.buffer);
		cmd->SCp.this_residual = cmd->SCp.buffer->length;
	}
}