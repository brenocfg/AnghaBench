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
struct drm_connector_state {int dummy; } ;
struct dpu_encoder_phys_vid {TYPE_1__* hw_intf; } ;
struct dpu_encoder_phys {int dummy; } ;
struct dpu_encoder_hw_resources {int /*<<< orphan*/ * intfs; } ;
struct TYPE_2__ {size_t idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG_VIDENC (struct dpu_encoder_phys_vid*,char*) ; 
 int /*<<< orphan*/  DPU_ERROR (char*,...) ; 
 size_t INTF_0 ; 
 int /*<<< orphan*/  INTF_MODE_VIDEO ; 
 struct dpu_encoder_phys_vid* to_dpu_encoder_phys_vid (struct dpu_encoder_phys*) ; 

__attribute__((used)) static void dpu_encoder_phys_vid_get_hw_resources(
		struct dpu_encoder_phys *phys_enc,
		struct dpu_encoder_hw_resources *hw_res,
		struct drm_connector_state *conn_state)
{
	struct dpu_encoder_phys_vid *vid_enc;

	if (!phys_enc || !hw_res) {
		DPU_ERROR("invalid arg(s), enc %d hw_res %d conn_state %d\n",
				phys_enc != 0, hw_res != 0, conn_state != 0);
		return;
	}

	vid_enc = to_dpu_encoder_phys_vid(phys_enc);
	if (!vid_enc->hw_intf) {
		DPU_ERROR("invalid arg(s), hw_intf\n");
		return;
	}

	DPU_DEBUG_VIDENC(vid_enc, "\n");
	hw_res->intfs[vid_enc->hw_intf->idx - INTF_0] = INTF_MODE_VIDEO;
}