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
struct scatterlist {int dummy; } ;
struct TYPE_2__ {struct scatterlist* sg; } ;
struct nvmet_tcp_cmd {size_t sg_idx; int nr_mapped; TYPE_1__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 

__attribute__((used)) static void nvmet_tcp_unmap_pdu_iovec(struct nvmet_tcp_cmd *cmd)
{
	struct scatterlist *sg;
	int i;

	sg = &cmd->req.sg[cmd->sg_idx];

	for (i = 0; i < cmd->nr_mapped; i++)
		kunmap(sg_page(&sg[i]));
}