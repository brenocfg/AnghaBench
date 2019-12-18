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
struct tty3270 {int /*<<< orphan*/  read; int /*<<< orphan*/  view; TYPE_1__* input; } ;
struct raw3270_request {struct tty3270* callback_data; int /*<<< orphan*/  callback; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int /*<<< orphan*/  TC_READMOD ; 
 int /*<<< orphan*/  raw3270_request_reset (struct raw3270_request*) ; 
 int /*<<< orphan*/  raw3270_request_set_cmd (struct raw3270_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw3270_request_set_data (struct raw3270_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int raw3270_start (int /*<<< orphan*/ *,struct raw3270_request*) ; 
 int raw3270_start_irq (int /*<<< orphan*/ *,struct raw3270_request*) ; 
 int /*<<< orphan*/  tty3270_read_callback ; 
 struct raw3270_request* xchg (int /*<<< orphan*/ *,struct raw3270_request*) ; 

__attribute__((used)) static void
tty3270_issue_read(struct tty3270 *tp, int lock)
{
	struct raw3270_request *rrq;
	int rc;

	rrq = xchg(&tp->read, 0);
	if (!rrq)
		/* Read already scheduled. */
		return;
	rrq->callback = tty3270_read_callback;
	rrq->callback_data = tp;
	raw3270_request_set_cmd(rrq, TC_READMOD);
	raw3270_request_set_data(rrq, tp->input->string, tp->input->len);
	/* Issue the read modified request. */
	if (lock) {
		rc = raw3270_start(&tp->view, rrq);
	} else
		rc = raw3270_start_irq(&tp->view, rrq);
	if (rc) {
		raw3270_request_reset(rrq);
		xchg(&tp->read, rrq);
	}
}