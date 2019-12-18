#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mvumi_hba {int /*<<< orphan*/  ib_max_size; TYPE_1__* pdev; } ;
struct mvumi_cmd {TYPE_2__* frame; int /*<<< orphan*/  frame_phys; int /*<<< orphan*/  queue_pointer; } ;
struct TYPE_5__ {scalar_t__ sg_counts; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_2__* dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mvumi_cmd*) ; 
 struct mvumi_cmd* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mvumi_internal_cmd_sgl (struct mvumi_hba*,struct mvumi_cmd*,unsigned int) ; 

__attribute__((used)) static struct mvumi_cmd *mvumi_create_internal_cmd(struct mvumi_hba *mhba,
				unsigned int buf_size)
{
	struct mvumi_cmd *cmd;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd) {
		dev_err(&mhba->pdev->dev, "failed to create a internal cmd\n");
		return NULL;
	}
	INIT_LIST_HEAD(&cmd->queue_pointer);

	cmd->frame = dma_alloc_coherent(&mhba->pdev->dev, mhba->ib_max_size,
			&cmd->frame_phys, GFP_KERNEL);
	if (!cmd->frame) {
		dev_err(&mhba->pdev->dev, "failed to allocate memory for FW"
			" frame,size = %d.\n", mhba->ib_max_size);
		kfree(cmd);
		return NULL;
	}

	if (buf_size) {
		if (mvumi_internal_cmd_sgl(mhba, cmd, buf_size)) {
			dev_err(&mhba->pdev->dev, "failed to allocate memory"
						" for internal frame\n");
			dma_free_coherent(&mhba->pdev->dev, mhba->ib_max_size,
					cmd->frame, cmd->frame_phys);
			kfree(cmd);
			return NULL;
		}
	} else
		cmd->frame->sg_counts = 0;

	return cmd;
}