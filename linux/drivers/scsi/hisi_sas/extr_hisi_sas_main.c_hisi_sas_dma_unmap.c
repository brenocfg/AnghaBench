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
struct TYPE_2__ {int /*<<< orphan*/  smp_req; } ;
struct sas_task {int task_proto; int num_scatter; TYPE_1__ smp_task; int /*<<< orphan*/  data_dir; int /*<<< orphan*/ * scatter; } ;
struct hisi_hba {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int SAS_PROTOCOL_SMP ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_protocol_ata (int) ; 

__attribute__((used)) static void hisi_sas_dma_unmap(struct hisi_hba *hisi_hba,
			       struct sas_task *task, int n_elem,
			       int n_elem_req)
{
	struct device *dev = hisi_hba->dev;

	if (!sas_protocol_ata(task->task_proto)) {
		if (task->num_scatter) {
			if (n_elem)
				dma_unmap_sg(dev, task->scatter,
					     task->num_scatter,
					     task->data_dir);
		} else if (task->task_proto & SAS_PROTOCOL_SMP) {
			if (n_elem_req)
				dma_unmap_sg(dev, &task->smp_task.smp_req,
					     1, DMA_TO_DEVICE);
		}
	}
}