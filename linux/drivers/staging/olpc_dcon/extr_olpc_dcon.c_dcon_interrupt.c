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
typedef  int u8 ;
struct dcon_priv {int switched; int /*<<< orphan*/  waitq; void* irq_time; int /*<<< orphan*/  pending_src; int /*<<< orphan*/  curr_src; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ (* read_status ) (int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 void* ktime_get () ; 
 TYPE_1__* pdata ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 scalar_t__ stub1 (int*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

irqreturn_t dcon_interrupt(int irq, void *id)
{
	struct dcon_priv *dcon = id;
	u8 status;

	if (pdata->read_status(&status))
		return IRQ_NONE;

	switch (status & 3) {
	case 3:
		pr_debug("DCONLOAD_MISSED interrupt\n");
		break;

	case 2:	/* switch to DCON mode */
	case 1: /* switch to CPU mode */
		dcon->switched = true;
		dcon->irq_time = ktime_get();
		wake_up(&dcon->waitq);
		break;

	case 0:
		/* workaround resume case:  the DCON (on 1.5) doesn't
		 * ever assert status 0x01 when switching to CPU mode
		 * during resume.  this is because DCONLOAD is de-asserted
		 * _immediately_ upon exiting S3, so the actual release
		 * of the DCON happened long before this point.
		 * see http://dev.laptop.org/ticket/9869
		 */
		if (dcon->curr_src != dcon->pending_src && !dcon->switched) {
			dcon->switched = true;
			dcon->irq_time = ktime_get();
			wake_up(&dcon->waitq);
			pr_debug("switching w/ status 0/0\n");
		} else {
			pr_debug("scanline interrupt w/CPU\n");
		}
	}

	return IRQ_HANDLED;
}