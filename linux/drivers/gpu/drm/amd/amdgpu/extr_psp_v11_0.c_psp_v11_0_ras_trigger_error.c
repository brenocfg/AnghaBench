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
struct ta_ras_trigger_error_input {int dummy; } ;
struct TYPE_4__ {struct ta_ras_trigger_error_input trigger_error; } ;
struct ta_ras_shared_memory {int ras_status; int /*<<< orphan*/  cmd_id; TYPE_2__ ras_in_message; } ;
struct TYPE_3__ {scalar_t__ ras_shared_buf; int /*<<< orphan*/  ras_initialized; } ;
struct psp_context {TYPE_1__ ras; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TA_RAS_COMMAND__TRIGGER_ERROR ; 
 int /*<<< orphan*/  memset (struct ta_ras_shared_memory*,int /*<<< orphan*/ ,int) ; 
 int psp_ras_invoke (struct psp_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int psp_v11_0_ras_trigger_error(struct psp_context *psp,
		struct ta_ras_trigger_error_input *info)
{
	struct ta_ras_shared_memory *ras_cmd;
	int ret;

	if (!psp->ras.ras_initialized)
		return -EINVAL;

	ras_cmd = (struct ta_ras_shared_memory *)psp->ras.ras_shared_buf;
	memset(ras_cmd, 0, sizeof(struct ta_ras_shared_memory));

	ras_cmd->cmd_id = TA_RAS_COMMAND__TRIGGER_ERROR;
	ras_cmd->ras_in_message.trigger_error = *info;

	ret = psp_ras_invoke(psp, ras_cmd->cmd_id);
	if (ret)
		return -EINVAL;

	return ras_cmd->ras_status;
}