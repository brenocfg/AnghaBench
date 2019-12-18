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
struct memstick_request {int dummy; } ;
struct memstick_dev {int /*<<< orphan*/  mrq_complete; struct memstick_request current_mrq; int /*<<< orphan*/  reg_addr; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  MS_TPC_SET_RW_REG_ADRS ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memstick_init_req (struct memstick_request*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int h_memstick_set_rw_addr(struct memstick_dev *card,
				  struct memstick_request **mrq)
{
	if (!(*mrq)) {
		memstick_init_req(&card->current_mrq, MS_TPC_SET_RW_REG_ADRS,
				  (char *)&card->reg_addr,
				  sizeof(card->reg_addr));
		*mrq = &card->current_mrq;
		return 0;
	} else {
		complete(&card->mrq_complete);
		return -EAGAIN;
	}
}