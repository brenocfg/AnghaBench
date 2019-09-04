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
struct rtas_error_log {int dummy; } ;
struct pseries_io_event {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  RTAS_DATA_BUF_SIZE ; 
 int /*<<< orphan*/  RTAS_IO_EVENTS ; 
 int /*<<< orphan*/  RTAS_VECTOR_EXTERNAL_INTERRUPT ; 
 int /*<<< orphan*/  __pa (scalar_t__) ; 
 int /*<<< orphan*/  atomic_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pseries_io_event*) ; 
 int /*<<< orphan*/  ioei_check_exception_token ; 
 struct pseries_io_event* ioei_find_event (struct rtas_error_log*) ; 
 scalar_t__ ioei_rtas_buf ; 
 int /*<<< orphan*/  pseries_ioei_notifier_list ; 
 int rtas_call (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virq_to_hw (int) ; 

__attribute__((used)) static irqreturn_t ioei_interrupt(int irq, void *dev_id)
{
	struct pseries_io_event *event;
	int rtas_rc;

	for (;;) {
		rtas_rc = rtas_call(ioei_check_exception_token, 6, 1, NULL,
				    RTAS_VECTOR_EXTERNAL_INTERRUPT,
				    virq_to_hw(irq),
				    RTAS_IO_EVENTS, 1 /* Time Critical */,
				    __pa(ioei_rtas_buf),
				    RTAS_DATA_BUF_SIZE);
		if (rtas_rc != 0)
			break;

		event = ioei_find_event((struct rtas_error_log *)ioei_rtas_buf);
		if (!event)
			continue;

		atomic_notifier_call_chain(&pseries_ioei_notifier_list,
					   0, event);
	}
	return IRQ_HANDLED;
}