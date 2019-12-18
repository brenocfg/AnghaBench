#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct hantro_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  enum vb2_buffer_state { ____Placeholder_vb2_buffer_state } vb2_buffer_state ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int VB2_BUF_STATE_DONE ; 
 int VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  VDPU_REG_AXI_CTRL ; 
 int /*<<< orphan*/  VDPU_REG_INTERRUPT ; 
 int VDPU_REG_INTERRUPT_DEC_IRQ ; 
 int /*<<< orphan*/  hantro_irq_done (struct hantro_dev*,int /*<<< orphan*/ ,int) ; 
 int vdpu_read (struct hantro_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdpu_write (struct hantro_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t rk3399_vdpu_irq(int irq, void *dev_id)
{
	struct hantro_dev *vpu = dev_id;
	enum vb2_buffer_state state;
	u32 status;

	status = vdpu_read(vpu, VDPU_REG_INTERRUPT);
	state = (status & VDPU_REG_INTERRUPT_DEC_IRQ) ?
		VB2_BUF_STATE_DONE : VB2_BUF_STATE_ERROR;

	vdpu_write(vpu, 0, VDPU_REG_INTERRUPT);
	vdpu_write(vpu, 0, VDPU_REG_AXI_CTRL);

	hantro_irq_done(vpu, 0, state);

	return IRQ_HANDLED;
}