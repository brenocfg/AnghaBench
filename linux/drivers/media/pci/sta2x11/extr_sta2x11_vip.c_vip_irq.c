#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sta2x11_vip {int tcount; TYPE_2__* active; int /*<<< orphan*/  sequence; int /*<<< orphan*/  bcount; int /*<<< orphan*/  overflow; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_4__ {TYPE_3__ vb2_buf; scalar_t__ sequence; } ;
struct TYPE_5__ {TYPE_1__ vb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVP_CTL ; 
 unsigned int DVP_CTL_ENA ; 
 int /*<<< orphan*/  DVP_ITS ; 
 unsigned int DVP_IT_FIFO ; 
 unsigned int DVP_IT_VSB ; 
 unsigned int DVP_IT_VST ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 unsigned int reg_read (struct sta2x11_vip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct sta2x11_vip*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  vb2_buffer_done (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t vip_irq(int irq, struct sta2x11_vip *vip)
{
	unsigned int status;

	status = reg_read(vip, DVP_ITS);

	if (!status)		/* No interrupt to handle */
		return IRQ_NONE;

	if (status & DVP_IT_FIFO)
		if (vip->overflow++ > 5)
			pr_info("VIP: fifo overflow\n");

	if ((status & DVP_IT_VST) && (status & DVP_IT_VSB)) {
		/* this is bad, we are too slow, hope the condition is gone
		 * on the next frame */
		return IRQ_HANDLED;
	}

	if (status & DVP_IT_VST)
		if ((++vip->tcount) < 2)
			return IRQ_HANDLED;
	if (status & DVP_IT_VSB) {
		vip->bcount++;
		return IRQ_HANDLED;
	}

	if (vip->active) { /* Acquisition is over on this buffer */
		/* Disable acquisition */
		reg_write(vip, DVP_CTL, reg_read(vip, DVP_CTL) & ~DVP_CTL_ENA);
		/* Remove the active buffer from the list */
		vip->active->vb.vb2_buf.timestamp = ktime_get_ns();
		vip->active->vb.sequence = vip->sequence++;
		vb2_buffer_done(&vip->active->vb.vb2_buf, VB2_BUF_STATE_DONE);
	}

	return IRQ_HANDLED;
}