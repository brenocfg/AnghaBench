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
typedef  int u32 ;
struct intel_vgpu {int dummy; } ;

/* Variables and functions */
 int PIPE_A ; 
 int PIPE_B ; 
 int PIPE_C ; 
#define  TRANS_DDI_EDP_INPUT_A_ON 131 
#define  TRANS_DDI_EDP_INPUT_A_ONOFF 130 
#define  TRANS_DDI_EDP_INPUT_B_ONOFF 129 
#define  TRANS_DDI_EDP_INPUT_C_ONOFF 128 
 int TRANS_DDI_EDP_INPUT_MASK ; 
 int /*<<< orphan*/  _TRANS_DDI_FUNC_CTL_EDP ; 
 int vgpu_vreg (struct intel_vgpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_edp_pipe(struct intel_vgpu *vgpu)
{
	u32 data = vgpu_vreg(vgpu, _TRANS_DDI_FUNC_CTL_EDP);
	int pipe = -1;

	switch (data & TRANS_DDI_EDP_INPUT_MASK) {
	case TRANS_DDI_EDP_INPUT_A_ON:
	case TRANS_DDI_EDP_INPUT_A_ONOFF:
		pipe = PIPE_A;
		break;
	case TRANS_DDI_EDP_INPUT_B_ONOFF:
		pipe = PIPE_B;
		break;
	case TRANS_DDI_EDP_INPUT_C_ONOFF:
		pipe = PIPE_C;
		break;
	}
	return pipe;
}