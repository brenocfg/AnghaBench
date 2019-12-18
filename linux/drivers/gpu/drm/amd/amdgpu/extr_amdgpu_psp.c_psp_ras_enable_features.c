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
typedef  union ta_ras_cmd_input {int dummy; } ta_ras_cmd_input ;
struct ta_ras_shared_memory {int ras_status; int /*<<< orphan*/  cmd_id; union ta_ras_cmd_input ras_in_message; } ;
struct TYPE_2__ {scalar_t__ ras_shared_buf; int /*<<< orphan*/  ras_initialized; } ;
struct psp_context {TYPE_1__ ras; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TA_RAS_COMMAND__DISABLE_FEATURES ; 
 int /*<<< orphan*/  TA_RAS_COMMAND__ENABLE_FEATURES ; 
 int /*<<< orphan*/  memset (struct ta_ras_shared_memory*,int /*<<< orphan*/ ,int) ; 
 int psp_ras_invoke (struct psp_context*,int /*<<< orphan*/ ) ; 

int psp_ras_enable_features(struct psp_context *psp,
		union ta_ras_cmd_input *info, bool enable)
{
	struct ta_ras_shared_memory *ras_cmd;
	int ret;

	if (!psp->ras.ras_initialized)
		return -EINVAL;

	ras_cmd = (struct ta_ras_shared_memory *)psp->ras.ras_shared_buf;
	memset(ras_cmd, 0, sizeof(struct ta_ras_shared_memory));

	if (enable)
		ras_cmd->cmd_id = TA_RAS_COMMAND__ENABLE_FEATURES;
	else
		ras_cmd->cmd_id = TA_RAS_COMMAND__DISABLE_FEATURES;

	ras_cmd->ras_in_message = *info;

	ret = psp_ras_invoke(psp, ras_cmd->cmd_id);
	if (ret)
		return -EINVAL;

	return ras_cmd->ras_status;
}