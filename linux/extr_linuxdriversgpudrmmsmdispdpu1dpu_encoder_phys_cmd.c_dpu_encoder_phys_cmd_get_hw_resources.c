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
struct drm_connector_state {int dummy; } ;
struct dpu_encoder_phys_cmd {int dummy; } ;
struct dpu_encoder_phys {scalar_t__ intf_idx; } ;
struct dpu_encoder_hw_resources {int /*<<< orphan*/ * intfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG_CMDENC (struct dpu_encoder_phys_cmd*,char*) ; 
 int /*<<< orphan*/  DPU_ERROR (char*,...) ; 
 scalar_t__ INTF_0 ; 
 scalar_t__ INTF_MAX ; 
 int /*<<< orphan*/  INTF_MODE_CMD ; 
 struct dpu_encoder_phys_cmd* to_dpu_encoder_phys_cmd (struct dpu_encoder_phys*) ; 

__attribute__((used)) static void dpu_encoder_phys_cmd_get_hw_resources(
		struct dpu_encoder_phys *phys_enc,
		struct dpu_encoder_hw_resources *hw_res,
		struct drm_connector_state *conn_state)
{
	struct dpu_encoder_phys_cmd *cmd_enc =
		to_dpu_encoder_phys_cmd(phys_enc);

	if (!phys_enc) {
		DPU_ERROR("invalid encoder\n");
		return;
	}

	if ((phys_enc->intf_idx - INTF_0) >= INTF_MAX) {
		DPU_ERROR("invalid intf idx:%d\n", phys_enc->intf_idx);
		return;
	}

	DPU_DEBUG_CMDENC(cmd_enc, "\n");
	hw_res->intfs[phys_enc->intf_idx - INTF_0] = INTF_MODE_CMD;
}