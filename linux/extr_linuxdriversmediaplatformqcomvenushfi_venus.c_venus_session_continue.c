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
struct venus_inst {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI_CMD_SESSION_CONTINUE ; 
 int venus_session_cmd (struct venus_inst*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int venus_session_continue(struct venus_inst *inst)
{
	return venus_session_cmd(inst, HFI_CMD_SESSION_CONTINUE);
}