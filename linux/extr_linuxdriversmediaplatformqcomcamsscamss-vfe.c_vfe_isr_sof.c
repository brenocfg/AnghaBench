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
struct vfe_output {int /*<<< orphan*/  sof; scalar_t__ wait_sof; } ;
struct vfe_device {int /*<<< orphan*/  output_lock; TYPE_1__* line; } ;
typedef  enum vfe_line_id { ____Placeholder_vfe_line_id } vfe_line_id ;
struct TYPE_2__ {struct vfe_output output; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void vfe_isr_sof(struct vfe_device *vfe, enum vfe_line_id line_id)
{
	struct vfe_output *output;
	unsigned long flags;

	spin_lock_irqsave(&vfe->output_lock, flags);
	output = &vfe->line[line_id].output;
	if (output->wait_sof) {
		output->wait_sof = 0;
		complete(&output->sof);
	}
	spin_unlock_irqrestore(&vfe->output_lock, flags);
}