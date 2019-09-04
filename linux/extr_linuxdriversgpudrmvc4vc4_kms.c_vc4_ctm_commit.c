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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct vc4_dev {TYPE_1__ ctm_manager; } ;
struct vc4_ctm_state {scalar_t__ fifo; struct drm_color_ctm* ctm; } ;
struct drm_color_ctm {int /*<<< orphan*/ * matrix; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HVS_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SCALER_OLEDCOEF0 ; 
 int /*<<< orphan*/  SCALER_OLEDCOEF0_B_TO_B ; 
 int /*<<< orphan*/  SCALER_OLEDCOEF0_B_TO_G ; 
 int /*<<< orphan*/  SCALER_OLEDCOEF0_B_TO_R ; 
 int /*<<< orphan*/  SCALER_OLEDCOEF1 ; 
 int /*<<< orphan*/  SCALER_OLEDCOEF1_G_TO_B ; 
 int /*<<< orphan*/  SCALER_OLEDCOEF1_G_TO_G ; 
 int /*<<< orphan*/  SCALER_OLEDCOEF1_G_TO_R ; 
 int /*<<< orphan*/  SCALER_OLEDCOEF2 ; 
 int /*<<< orphan*/  SCALER_OLEDCOEF2_R_TO_B ; 
 int /*<<< orphan*/  SCALER_OLEDCOEF2_R_TO_G ; 
 int /*<<< orphan*/  SCALER_OLEDCOEF2_R_TO_R ; 
 int /*<<< orphan*/  SCALER_OLEDOFFS ; 
 int /*<<< orphan*/  SCALER_OLEDOFFS_DISPFIFO ; 
 int VC4_SET_FIELD (scalar_t__,int /*<<< orphan*/ ) ; 
 struct vc4_ctm_state* to_vc4_ctm_state (int /*<<< orphan*/ ) ; 
 scalar_t__ vc4_ctm_s31_32_to_s0_9 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vc4_ctm_commit(struct vc4_dev *vc4, struct drm_atomic_state *state)
{
	struct vc4_ctm_state *ctm_state = to_vc4_ctm_state(vc4->ctm_manager.state);
	struct drm_color_ctm *ctm = ctm_state->ctm;

	if (ctm_state->fifo) {
		HVS_WRITE(SCALER_OLEDCOEF2,
			  VC4_SET_FIELD(vc4_ctm_s31_32_to_s0_9(ctm->matrix[0]),
					SCALER_OLEDCOEF2_R_TO_R) |
			  VC4_SET_FIELD(vc4_ctm_s31_32_to_s0_9(ctm->matrix[3]),
					SCALER_OLEDCOEF2_R_TO_G) |
			  VC4_SET_FIELD(vc4_ctm_s31_32_to_s0_9(ctm->matrix[6]),
					SCALER_OLEDCOEF2_R_TO_B));
		HVS_WRITE(SCALER_OLEDCOEF1,
			  VC4_SET_FIELD(vc4_ctm_s31_32_to_s0_9(ctm->matrix[1]),
					SCALER_OLEDCOEF1_G_TO_R) |
			  VC4_SET_FIELD(vc4_ctm_s31_32_to_s0_9(ctm->matrix[4]),
					SCALER_OLEDCOEF1_G_TO_G) |
			  VC4_SET_FIELD(vc4_ctm_s31_32_to_s0_9(ctm->matrix[7]),
					SCALER_OLEDCOEF1_G_TO_B));
		HVS_WRITE(SCALER_OLEDCOEF0,
			  VC4_SET_FIELD(vc4_ctm_s31_32_to_s0_9(ctm->matrix[2]),
					SCALER_OLEDCOEF0_B_TO_R) |
			  VC4_SET_FIELD(vc4_ctm_s31_32_to_s0_9(ctm->matrix[5]),
					SCALER_OLEDCOEF0_B_TO_G) |
			  VC4_SET_FIELD(vc4_ctm_s31_32_to_s0_9(ctm->matrix[8]),
					SCALER_OLEDCOEF0_B_TO_B));
	}

	HVS_WRITE(SCALER_OLEDOFFS,
		  VC4_SET_FIELD(ctm_state->fifo, SCALER_OLEDOFFS_DISPFIFO));
}