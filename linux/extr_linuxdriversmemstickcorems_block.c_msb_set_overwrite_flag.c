#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {void* overwrite_flag; } ;
struct TYPE_6__ {int /*<<< orphan*/  cp; void* page_address; int /*<<< orphan*/  block_address; } ;
struct TYPE_5__ {TYPE_1__ extra_data; TYPE_3__ param; } ;
struct msb_data {int command_need_oob; int /*<<< orphan*/  command_value; TYPE_2__ regs; scalar_t__ read_only; } ;

/* Variables and functions */
 int EROFS ; 
 int /*<<< orphan*/  MEMSTICK_CP_OVERWRITE ; 
 int /*<<< orphan*/  MS_CMD_BLOCK_WRITE ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_verbose (char*,void*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  h_msb_send_command ; 
 int msb_run_state_machine (struct msb_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msb_set_overwrite_flag(struct msb_data *msb,
						u16 pba, u8 page, u8 flag)
{
	if (msb->read_only)
		return -EROFS;

	msb->regs.param.block_address = cpu_to_be16(pba);
	msb->regs.param.page_address = page;
	msb->regs.param.cp = MEMSTICK_CP_OVERWRITE;
	msb->regs.extra_data.overwrite_flag = flag;
	msb->command_value = MS_CMD_BLOCK_WRITE;
	msb->command_need_oob = true;

	dbg_verbose("changing overwrite flag to %02x for sector %d, page %d",
							flag, pba, page);
	return msb_run_state_machine(msb, h_msb_send_command);
}