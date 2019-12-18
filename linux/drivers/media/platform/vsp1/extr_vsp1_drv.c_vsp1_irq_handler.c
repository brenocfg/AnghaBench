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
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  pipe; } ;
struct vsp1_rwpf {TYPE_1__ entity; } ;
struct vsp1_device {struct vsp1_rwpf** wpf; TYPE_2__* info; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {unsigned int wpf_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int VI6_WFP_IRQ_STA_DFE ; 
 int VI6_WFP_IRQ_STA_FRE ; 
 int /*<<< orphan*/  VI6_WPF_IRQ_STA (unsigned int) ; 
 int /*<<< orphan*/  vsp1_pipeline_frame_end (int /*<<< orphan*/ ) ; 
 int vsp1_read (struct vsp1_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsp1_write (struct vsp1_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t vsp1_irq_handler(int irq, void *data)
{
	u32 mask = VI6_WFP_IRQ_STA_DFE | VI6_WFP_IRQ_STA_FRE;
	struct vsp1_device *vsp1 = data;
	irqreturn_t ret = IRQ_NONE;
	unsigned int i;
	u32 status;

	for (i = 0; i < vsp1->info->wpf_count; ++i) {
		struct vsp1_rwpf *wpf = vsp1->wpf[i];

		if (wpf == NULL)
			continue;

		status = vsp1_read(vsp1, VI6_WPF_IRQ_STA(i));
		vsp1_write(vsp1, VI6_WPF_IRQ_STA(i), ~status & mask);

		if (status & VI6_WFP_IRQ_STA_DFE) {
			vsp1_pipeline_frame_end(wpf->entity.pipe);
			ret = IRQ_HANDLED;
		}
	}

	return ret;
}