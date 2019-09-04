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
typedef  int /*<<< orphan*/  u8 ;
struct msb_data {int state; } ;
struct memstick_request {int /*<<< orphan*/  need_card_int; scalar_t__ error; } ;
struct memstick_dev {struct memstick_request current_mrq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  MSB_RS_CONFIRM 129 
#define  MSB_RS_SEND 128 
 int /*<<< orphan*/  MS_CMD_RESET ; 
 int /*<<< orphan*/  MS_TPC_SET_CMD ; 
 struct msb_data* memstick_get_drvdata (struct memstick_dev*) ; 
 int /*<<< orphan*/  memstick_init_req (struct memstick_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int msb_exit_state_machine (struct msb_data*,scalar_t__) ; 

__attribute__((used)) static int h_msb_reset(struct memstick_dev *card,
					struct memstick_request **out_mrq)
{
	u8 command = MS_CMD_RESET;
	struct msb_data *msb = memstick_get_drvdata(card);
	struct memstick_request *mrq = *out_mrq = &card->current_mrq;

	if (mrq->error)
		return msb_exit_state_machine(msb, mrq->error);

	switch (msb->state) {
	case MSB_RS_SEND:
		memstick_init_req(mrq, MS_TPC_SET_CMD, &command, 1);
		mrq->need_card_int = 0;
		msb->state = MSB_RS_CONFIRM;
		return 0;
	case MSB_RS_CONFIRM:
		return msb_exit_state_machine(msb, 0);
	}
	BUG();
}