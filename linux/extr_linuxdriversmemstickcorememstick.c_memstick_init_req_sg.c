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
struct scatterlist {int dummy; } ;
struct memstick_request {unsigned char tpc; int long_data; int need_card_int; struct scatterlist sg; int /*<<< orphan*/  data_dir; } ;

/* Variables and functions */
 unsigned char MS_TPC_EX_SET_CMD ; 
 unsigned char MS_TPC_SET_CMD ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  WRITE ; 

void memstick_init_req_sg(struct memstick_request *mrq, unsigned char tpc,
			  const struct scatterlist *sg)
{
	mrq->tpc = tpc;
	if (tpc & 8)
		mrq->data_dir = WRITE;
	else
		mrq->data_dir = READ;

	mrq->sg = *sg;
	mrq->long_data = 1;

	if (tpc == MS_TPC_SET_CMD || tpc == MS_TPC_EX_SET_CMD)
		mrq->need_card_int = 1;
	else
		mrq->need_card_int = 0;
}