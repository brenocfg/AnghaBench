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
typedef  int u16 ;
struct drxd_state {scalar_t__ operation_mode; int m_EcOcRegOcModeLop; scalar_t__ enable_parallel; scalar_t__ insert_rs_byte; } ;

/* Variables and functions */
 int B_EC_OC_REG_OC_MODE_HIP_MPG_BUS_SRC_MONITOR ; 
 int /*<<< orphan*/  EC_OC_REG_IPR_INV_MPG__A ; 
 int EC_OC_REG_OC_MODE_HIP_MPG_PAR_VAL_DISABLE ; 
 int EC_OC_REG_OC_MODE_HIP_MPG_PAR_VAL_ENABLE ; 
 int EC_OC_REG_OC_MODE_HIP_MPG_PAR_VAL__M ; 
 int /*<<< orphan*/  EC_OC_REG_OC_MODE_HIP__A ; 
 int EC_OC_REG_OC_MODE_LOP_MPG_TRM_MDE_SERIAL ; 
 int EC_OC_REG_OC_MODE_LOP_MPG_TRM_MDE__M ; 
 int EC_OC_REG_OC_MODE_LOP_PAR_ENA_DISABLE ; 
 int EC_OC_REG_OC_MODE_LOP_PAR_ENA__M ; 
 int /*<<< orphan*/  EC_OC_REG_OC_MODE_LOP__A ; 
 int /*<<< orphan*/  EC_OC_REG_OC_MPG_SIO__A ; 
 int EC_OC_REG_OC_MPG_SIO__M ; 
 scalar_t__ OM_DVBT_Diversity_Front ; 
 int Write16 (struct drxd_state*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ConfigureMPEGOutput(struct drxd_state *state, int bEnableOutput)
{
	int status;

	do {
		u16 EcOcRegIprInvMpg = 0;
		u16 EcOcRegOcModeLop = 0;
		u16 EcOcRegOcModeHip = 0;
		u16 EcOcRegOcMpgSio = 0;

		/*CHK_ERROR(Read16(state, EC_OC_REG_OC_MODE_LOP__A, &EcOcRegOcModeLop, 0)); */

		if (state->operation_mode == OM_DVBT_Diversity_Front) {
			if (bEnableOutput) {
				EcOcRegOcModeHip |=
				    B_EC_OC_REG_OC_MODE_HIP_MPG_BUS_SRC_MONITOR;
			} else
				EcOcRegOcMpgSio |= EC_OC_REG_OC_MPG_SIO__M;
			EcOcRegOcModeLop |=
			    EC_OC_REG_OC_MODE_LOP_PAR_ENA_DISABLE;
		} else {
			EcOcRegOcModeLop = state->m_EcOcRegOcModeLop;

			if (bEnableOutput)
				EcOcRegOcMpgSio &= (~(EC_OC_REG_OC_MPG_SIO__M));
			else
				EcOcRegOcMpgSio |= EC_OC_REG_OC_MPG_SIO__M;

			/* Don't Insert RS Byte */
			if (state->insert_rs_byte) {
				EcOcRegOcModeLop &=
				    (~(EC_OC_REG_OC_MODE_LOP_PAR_ENA__M));
				EcOcRegOcModeHip &=
				    (~EC_OC_REG_OC_MODE_HIP_MPG_PAR_VAL__M);
				EcOcRegOcModeHip |=
				    EC_OC_REG_OC_MODE_HIP_MPG_PAR_VAL_ENABLE;
			} else {
				EcOcRegOcModeLop |=
				    EC_OC_REG_OC_MODE_LOP_PAR_ENA_DISABLE;
				EcOcRegOcModeHip &=
				    (~EC_OC_REG_OC_MODE_HIP_MPG_PAR_VAL__M);
				EcOcRegOcModeHip |=
				    EC_OC_REG_OC_MODE_HIP_MPG_PAR_VAL_DISABLE;
			}

			/* Mode = Parallel */
			if (state->enable_parallel)
				EcOcRegOcModeLop &=
				    (~(EC_OC_REG_OC_MODE_LOP_MPG_TRM_MDE__M));
			else
				EcOcRegOcModeLop |=
				    EC_OC_REG_OC_MODE_LOP_MPG_TRM_MDE_SERIAL;
		}
		/* Invert Data */
		/* EcOcRegIprInvMpg |= 0x00FF; */
		EcOcRegIprInvMpg &= (~(0x00FF));

		/* Invert Error ( we don't use the pin ) */
		/*  EcOcRegIprInvMpg |= 0x0100; */
		EcOcRegIprInvMpg &= (~(0x0100));

		/* Invert Start ( we don't use the pin ) */
		/* EcOcRegIprInvMpg |= 0x0200; */
		EcOcRegIprInvMpg &= (~(0x0200));

		/* Invert Valid ( we don't use the pin ) */
		/* EcOcRegIprInvMpg |= 0x0400; */
		EcOcRegIprInvMpg &= (~(0x0400));

		/* Invert Clock */
		/* EcOcRegIprInvMpg |= 0x0800; */
		EcOcRegIprInvMpg &= (~(0x0800));

		/* EcOcRegOcModeLop =0x05; */
		status = Write16(state, EC_OC_REG_IPR_INV_MPG__A, EcOcRegIprInvMpg, 0);
		if (status < 0)
			break;
		status = Write16(state, EC_OC_REG_OC_MODE_LOP__A, EcOcRegOcModeLop, 0);
		if (status < 0)
			break;
		status = Write16(state, EC_OC_REG_OC_MODE_HIP__A, EcOcRegOcModeHip, 0x0000);
		if (status < 0)
			break;
		status = Write16(state, EC_OC_REG_OC_MPG_SIO__A, EcOcRegOcMpgSio, 0);
		if (status < 0)
			break;
	} while (0);
	return status;
}