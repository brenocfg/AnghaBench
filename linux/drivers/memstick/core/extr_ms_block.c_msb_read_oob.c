#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct ms_extra_data_register {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  cp; scalar_t__ page_address; int /*<<< orphan*/  block_address; } ;
struct TYPE_3__ {struct ms_extra_data_register extra_data; TYPE_2__ param; } ;
struct msb_data {scalar_t__ block_count; TYPE_1__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int EUCLEAN ; 
 int /*<<< orphan*/  MEMSTICK_CP_EXTRA ; 
 int /*<<< orphan*/  cpu_to_be16 (scalar_t__) ; 
 int /*<<< orphan*/  h_msb_read_page ; 
 int msb_run_state_machine (struct msb_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  pr_notice (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int msb_read_oob(struct msb_data *msb, u16 pba, u16 page,
	struct ms_extra_data_register *extra)
{
	int error;

	BUG_ON(!extra);
	msb->regs.param.block_address = cpu_to_be16(pba);
	msb->regs.param.page_address = page;
	msb->regs.param.cp = MEMSTICK_CP_EXTRA;

	if (pba > msb->block_count) {
		pr_err("BUG: attempt to read beyond the end of card at pba %d", pba);
		return -EINVAL;
	}

	error = msb_run_state_machine(msb, h_msb_read_page);
	*extra = msb->regs.extra_data;

	if (error == -EUCLEAN) {
		pr_notice("correctable error on pba %d, page %d",
			pba, page);
		return 0;
	}

	return error;
}