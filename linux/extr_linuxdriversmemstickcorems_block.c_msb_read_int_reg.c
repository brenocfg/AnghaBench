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
struct msb_data {int state; int int_polling; int caps; scalar_t__ int_timeout; TYPE_1__* card; } ;
struct memstick_request {int need_card_int; int /*<<< orphan*/  int_reg; int /*<<< orphan*/ * data; int /*<<< orphan*/  error; } ;
struct TYPE_2__ {struct memstick_request current_mrq; } ;

/* Variables and functions */
 int MEMSTICK_CAP_AUTO_GET_INT ; 
 int /*<<< orphan*/  MEMSTICK_INT_CMDNAK ; 
 int /*<<< orphan*/  MS_TPC_GET_INT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memstick_init_req (struct memstick_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int msb_read_int_reg(struct msb_data *msb, long timeout)
{
	struct memstick_request *mrq = &msb->card->current_mrq;

	WARN_ON(msb->state == -1);

	if (!msb->int_polling) {
		msb->int_timeout = jiffies +
			msecs_to_jiffies(timeout == -1 ? 500 : timeout);
		msb->int_polling = true;
	} else if (time_after(jiffies, msb->int_timeout)) {
		mrq->data[0] = MEMSTICK_INT_CMDNAK;
		return 0;
	}

	if ((msb->caps & MEMSTICK_CAP_AUTO_GET_INT) &&
				mrq->need_card_int && !mrq->error) {
		mrq->data[0] = mrq->int_reg;
		mrq->need_card_int = false;
		return 0;
	} else {
		memstick_init_req(mrq, MS_TPC_GET_INT, NULL, 1);
		return 1;
	}
}