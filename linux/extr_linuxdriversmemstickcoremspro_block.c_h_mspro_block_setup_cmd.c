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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ u64 ;
struct mspro_param_register {int /*<<< orphan*/  data_address; int /*<<< orphan*/  tpc_param; int /*<<< orphan*/  data_count; int /*<<< orphan*/  system; } ;
struct mspro_block_data {size_t page_size; int /*<<< orphan*/  mrq_handler; int /*<<< orphan*/  system; } ;
struct memstick_dev {int /*<<< orphan*/  current_mrq; int /*<<< orphan*/  next_request; } ;
typedef  int /*<<< orphan*/  param ;

/* Variables and functions */
 int /*<<< orphan*/  MS_TPC_WRITE_REG ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (scalar_t__,size_t) ; 
 int /*<<< orphan*/  h_mspro_block_req_init ; 
 int /*<<< orphan*/  h_mspro_block_transfer_data ; 
 struct mspro_block_data* memstick_get_drvdata (struct memstick_dev*) ; 
 int /*<<< orphan*/  memstick_init_req (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mspro_param_register*,int) ; 

__attribute__((used)) static void h_mspro_block_setup_cmd(struct memstick_dev *card, u64 offset,
				    size_t length)
{
	struct mspro_block_data *msb = memstick_get_drvdata(card);
	struct mspro_param_register param = {
		.system = msb->system,
		.data_count = cpu_to_be16((uint16_t)(length / msb->page_size)),
		/* ISO C90 warning precludes direct initialization for now. */
		.data_address = 0,
		.tpc_param = 0
	};

	do_div(offset, msb->page_size);
	param.data_address = cpu_to_be32((uint32_t)offset);

	card->next_request = h_mspro_block_req_init;
	msb->mrq_handler = h_mspro_block_transfer_data;
	memstick_init_req(&card->current_mrq, MS_TPC_WRITE_REG,
			  &param, sizeof(param));
}