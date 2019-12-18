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
struct scsi_dif_task_params {int dif_block_size_log; scalar_t__ dif_on_host; scalar_t__ dif_on_network; } ;
struct iscsi_dif_flags {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_DIF_FLAGS_DIF_TO_PEER ; 
 int /*<<< orphan*/  ISCSI_DIF_FLAGS_HOST_INTERFACE ; 
 int /*<<< orphan*/  ISCSI_DIF_FLAGS_PROT_INTERVAL_SIZE_LOG ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
init_dif_context_flags(struct iscsi_dif_flags *ctx_dif_flags,
		       struct scsi_dif_task_params *dif_task_params)
{
	if (!dif_task_params)
		return;

	SET_FIELD(ctx_dif_flags->flags, ISCSI_DIF_FLAGS_PROT_INTERVAL_SIZE_LOG,
		  dif_task_params->dif_block_size_log);
	SET_FIELD(ctx_dif_flags->flags, ISCSI_DIF_FLAGS_DIF_TO_PEER,
		  dif_task_params->dif_on_network ? 1 : 0);
	SET_FIELD(ctx_dif_flags->flags, ISCSI_DIF_FLAGS_HOST_INTERFACE,
		  dif_task_params->dif_on_host ? 1 : 0);
}