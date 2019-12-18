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
typedef  void* u32 ;
struct a6xx_hfi_msg_gmu_init_cmd {int boot_state; void* dbg_buffer_size; void* dbg_buffer_addr; int /*<<< orphan*/  member_0; } ;
struct a6xx_gmu {TYPE_1__* debug; } ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_2__ {scalar_t__ size; scalar_t__ iova; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI_H2F_MSG_INIT ; 
 int a6xx_hfi_send_msg (struct a6xx_gmu*,int /*<<< orphan*/ ,struct a6xx_hfi_msg_gmu_init_cmd*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int a6xx_hfi_send_gmu_init(struct a6xx_gmu *gmu, int boot_state)
{
	struct a6xx_hfi_msg_gmu_init_cmd msg = { 0 };

	msg.dbg_buffer_addr = (u32) gmu->debug->iova;
	msg.dbg_buffer_size = (u32) gmu->debug->size;
	msg.boot_state = boot_state;

	return a6xx_hfi_send_msg(gmu, HFI_H2F_MSG_INIT, &msg, sizeof(msg),
		NULL, 0);
}