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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/ * mode_ptr; } ;
struct TYPE_5__ {TYPE_3__ cure_poison; } ;
struct ta_ras_shared_memory {int ras_status; int /*<<< orphan*/  cmd_id; TYPE_2__ ras_in_message; } ;
struct TYPE_4__ {scalar_t__ ras_shared_buf; int /*<<< orphan*/  ras_initialized; } ;
struct psp_context {TYPE_1__ ras; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TA_RAS_COMMAND__CURE_POISON ; 
 int /*<<< orphan*/  memset (struct ta_ras_shared_memory*,int /*<<< orphan*/ ,int) ; 
 int psp_ras_invoke (struct psp_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int psp_v11_0_ras_cure_posion(struct psp_context *psp, uint64_t *mode_ptr)
{
#if 0
	// not support yet.
	struct ta_ras_shared_memory *ras_cmd;
	int ret;

	if (!psp->ras.ras_initialized)
		return -EINVAL;

	ras_cmd = (struct ta_ras_shared_memory *)psp->ras.ras_shared_buf;
	memset(ras_cmd, 0, sizeof(struct ta_ras_shared_memory));

	ras_cmd->cmd_id = TA_RAS_COMMAND__CURE_POISON;
	ras_cmd->ras_in_message.cure_poison.mode_ptr = mode_ptr;

	ret = psp_ras_invoke(psp, ras_cmd->cmd_id);
	if (ret)
		return -EINVAL;

	return ras_cmd->ras_status;
#else
	return -EINVAL;
#endif
}