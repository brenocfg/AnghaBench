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
typedef  int u16 ;
struct TYPE_2__ {int bandwidth_hz; } ;
struct drxd_state {scalar_t__ operation_mode; int /*<<< orphan*/  m_DiversityDelay6MHZ; int /*<<< orphan*/  m_DiversityDelay8MHZ; TYPE_1__ props; int /*<<< orphan*/  m_StartDiversityEnd; int /*<<< orphan*/  m_StartDiversityFront; } ;

/* Variables and functions */
 int B_EQ_REG_RC_SEL_CAR_DIV_ON ; 
 int B_EQ_REG_RC_SEL_CAR_FFTMODE__M ; 
 int B_EQ_REG_RC_SEL_CAR_LOCAL_A_CC ; 
 int B_EQ_REG_RC_SEL_CAR_MEAS_A_CC ; 
 int B_EQ_REG_RC_SEL_CAR_PASS_A_CC ; 
 int /*<<< orphan*/  B_EQ_REG_RC_SEL_CAR__A ; 
 scalar_t__ OM_DVBT_Diversity_End ; 
 scalar_t__ OM_DVBT_Diversity_Front ; 
 int Read16 (struct drxd_state*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int Write16 (struct drxd_state*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int WriteTable (struct drxd_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int StartDiversity(struct drxd_state *state)
{
	int status = 0;
	u16 rcControl;

	do {
		if (state->operation_mode == OM_DVBT_Diversity_Front) {
			status = WriteTable(state, state->m_StartDiversityFront);
			if (status < 0)
				break;
		} else if (state->operation_mode == OM_DVBT_Diversity_End) {
			status = WriteTable(state, state->m_StartDiversityEnd);
			if (status < 0)
				break;
			if (state->props.bandwidth_hz == 8000000) {
				status = WriteTable(state, state->m_DiversityDelay8MHZ);
				if (status < 0)
					break;
			} else {
				status = WriteTable(state, state->m_DiversityDelay6MHZ);
				if (status < 0)
					break;
			}

			status = Read16(state, B_EQ_REG_RC_SEL_CAR__A, &rcControl, 0);
			if (status < 0)
				break;
			rcControl &= ~(B_EQ_REG_RC_SEL_CAR_FFTMODE__M);
			rcControl |= B_EQ_REG_RC_SEL_CAR_DIV_ON |
			    /*  combining enabled */
			    B_EQ_REG_RC_SEL_CAR_MEAS_A_CC |
			    B_EQ_REG_RC_SEL_CAR_PASS_A_CC |
			    B_EQ_REG_RC_SEL_CAR_LOCAL_A_CC;
			status = Write16(state, B_EQ_REG_RC_SEL_CAR__A, rcControl, 0);
			if (status < 0)
				break;
		}
	} while (0);
	return status;
}