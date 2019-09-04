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
struct mspro_block_data {int /*<<< orphan*/  mrq_handler; } ;
struct TYPE_2__ {int error; } ;
struct memstick_dev {TYPE_1__ current_mrq; int /*<<< orphan*/  mrq_complete; int /*<<< orphan*/  host; int /*<<< orphan*/  next_request; } ;

/* Variables and functions */
 int /*<<< orphan*/  MS_TPC_GET_INT ; 
 int /*<<< orphan*/  h_mspro_block_req_init ; 
 int /*<<< orphan*/  h_mspro_block_wait_for_ced ; 
 struct mspro_block_data* memstick_get_drvdata (struct memstick_dev*) ; 
 int /*<<< orphan*/  memstick_init_req (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memstick_new_req (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mspro_block_wait_for_ced(struct memstick_dev *card)
{
	struct mspro_block_data *msb = memstick_get_drvdata(card);

	card->next_request = h_mspro_block_req_init;
	msb->mrq_handler = h_mspro_block_wait_for_ced;
	memstick_init_req(&card->current_mrq, MS_TPC_GET_INT, NULL, 1);
	memstick_new_req(card->host);
	wait_for_completion(&card->mrq_complete);
	return card->current_mrq.error;
}