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
struct TYPE_2__ {int /*<<< orphan*/  sch_no; int /*<<< orphan*/  ssid; } ;
struct subchannel {int /*<<< orphan*/  dev; TYPE_1__ schid; } ;
struct irb {int dummy; } ;
struct chsc_request {int /*<<< orphan*/  completion; int /*<<< orphan*/  irb; } ;
struct chsc_private {struct chsc_request* request; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHSC_LOG (int,char*) ; 
 int /*<<< orphan*/  CHSC_LOG_HEX (int,struct irb*,int) ; 
 int /*<<< orphan*/  CHSC_MSG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQIO_CSC ; 
 int /*<<< orphan*/  cio_irb ; 
 int /*<<< orphan*/  cio_update_schib (struct subchannel*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct chsc_private* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inc_irq_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct irb*,int) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 struct irb* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void chsc_subchannel_irq(struct subchannel *sch)
{
	struct chsc_private *private = dev_get_drvdata(&sch->dev);
	struct chsc_request *request = private->request;
	struct irb *irb = this_cpu_ptr(&cio_irb);

	CHSC_LOG(4, "irb");
	CHSC_LOG_HEX(4, irb, sizeof(*irb));
	inc_irq_stat(IRQIO_CSC);

	/* Copy irb to provided request and set done. */
	if (!request) {
		CHSC_MSG(0, "Interrupt on sch 0.%x.%04x with no request\n",
			 sch->schid.ssid, sch->schid.sch_no);
		return;
	}
	private->request = NULL;
	memcpy(&request->irb, irb, sizeof(*irb));
	cio_update_schib(sch);
	complete(&request->completion);
	put_device(&sch->dev);
}