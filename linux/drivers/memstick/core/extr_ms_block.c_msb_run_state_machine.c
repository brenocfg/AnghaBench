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
struct msb_data {int state; int int_polling; int exit_error; struct memstick_dev* card; } ;
struct memstick_dev {int (* next_request ) (struct memstick_dev*,struct memstick_request**) ;int /*<<< orphan*/  mrq_complete; int /*<<< orphan*/  host; int /*<<< orphan*/  current_mrq; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memstick_new_req (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int msb_run_state_machine(struct msb_data *msb, int   (*state_func)
		(struct memstick_dev *card, struct memstick_request **req))
{
	struct memstick_dev *card = msb->card;

	WARN_ON(msb->state != -1);
	msb->int_polling = false;
	msb->state = 0;
	msb->exit_error = 0;

	memset(&card->current_mrq, 0, sizeof(card->current_mrq));

	card->next_request = state_func;
	memstick_new_req(card->host);
	wait_for_completion(&card->mrq_complete);

	WARN_ON(msb->state != -1);
	return msb->exit_error;
}