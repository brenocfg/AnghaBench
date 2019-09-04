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
struct stv0367_state {int dummy; } ;
typedef  enum stv0367cab_mod { ____Placeholder_stv0367cab_mod } stv0367cab_mod ;

/* Variables and functions */
 int /*<<< orphan*/  F367CAB_QAM_MODE ; 
#define  FE_CAB_MOD_QAM1024 135 
#define  FE_CAB_MOD_QAM128 134 
#define  FE_CAB_MOD_QAM16 133 
#define  FE_CAB_MOD_QAM256 132 
#define  FE_CAB_MOD_QAM32 131 
#define  FE_CAB_MOD_QAM4 130 
#define  FE_CAB_MOD_QAM512 129 
#define  FE_CAB_MOD_QAM64 128 
 int /*<<< orphan*/  R367CAB_AGC_PWR_REF_L ; 
 int /*<<< orphan*/  R367CAB_EQU_CRL_LD_SEN ; 
 int /*<<< orphan*/  R367CAB_EQU_CRL_LIMITER ; 
 int /*<<< orphan*/  R367CAB_EQU_CRL_LPF_GAIN ; 
 int /*<<< orphan*/  R367CAB_EQU_CTR_LPF_GAIN ; 
 int /*<<< orphan*/  R367CAB_EQU_PNT_GAIN ; 
 int /*<<< orphan*/  R367CAB_FSM_STATE ; 
 int /*<<< orphan*/  R367CAB_IQDEM_ADJ_AGC_REF ; 
 int /*<<< orphan*/  stv0367_writebits (struct stv0367_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stv0367_writereg (struct stv0367_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum stv0367cab_mod stv0367cab_SetQamSize(struct stv0367_state *state,
						 u32 SymbolRate,
						 enum stv0367cab_mod QAMSize)
{
	/* Set QAM size */
	stv0367_writebits(state, F367CAB_QAM_MODE, QAMSize);

	/* Set Registers settings specific to the QAM size */
	switch (QAMSize) {
	case FE_CAB_MOD_QAM4:
		stv0367_writereg(state, R367CAB_IQDEM_ADJ_AGC_REF, 0x00);
		break;
	case FE_CAB_MOD_QAM16:
		stv0367_writereg(state, R367CAB_AGC_PWR_REF_L, 0x64);
		stv0367_writereg(state, R367CAB_IQDEM_ADJ_AGC_REF, 0x00);
		stv0367_writereg(state, R367CAB_FSM_STATE, 0x90);
		stv0367_writereg(state, R367CAB_EQU_CTR_LPF_GAIN, 0xc1);
		stv0367_writereg(state, R367CAB_EQU_CRL_LPF_GAIN, 0xa7);
		stv0367_writereg(state, R367CAB_EQU_CRL_LD_SEN, 0x95);
		stv0367_writereg(state, R367CAB_EQU_CRL_LIMITER, 0x40);
		stv0367_writereg(state, R367CAB_EQU_PNT_GAIN, 0x8a);
		break;
	case FE_CAB_MOD_QAM32:
		stv0367_writereg(state, R367CAB_IQDEM_ADJ_AGC_REF, 0x00);
		stv0367_writereg(state, R367CAB_AGC_PWR_REF_L, 0x6e);
		stv0367_writereg(state, R367CAB_FSM_STATE, 0xb0);
		stv0367_writereg(state, R367CAB_EQU_CTR_LPF_GAIN, 0xc1);
		stv0367_writereg(state, R367CAB_EQU_CRL_LPF_GAIN, 0xb7);
		stv0367_writereg(state, R367CAB_EQU_CRL_LD_SEN, 0x9d);
		stv0367_writereg(state, R367CAB_EQU_CRL_LIMITER, 0x7f);
		stv0367_writereg(state, R367CAB_EQU_PNT_GAIN, 0xa7);
		break;
	case FE_CAB_MOD_QAM64:
		stv0367_writereg(state, R367CAB_IQDEM_ADJ_AGC_REF, 0x82);
		stv0367_writereg(state, R367CAB_AGC_PWR_REF_L, 0x5a);
		if (SymbolRate > 4500000) {
			stv0367_writereg(state, R367CAB_FSM_STATE, 0xb0);
			stv0367_writereg(state, R367CAB_EQU_CTR_LPF_GAIN, 0xc1);
			stv0367_writereg(state, R367CAB_EQU_CRL_LPF_GAIN, 0xa5);
		} else if (SymbolRate > 2500000) {
			stv0367_writereg(state, R367CAB_FSM_STATE, 0xa0);
			stv0367_writereg(state, R367CAB_EQU_CTR_LPF_GAIN, 0xc1);
			stv0367_writereg(state, R367CAB_EQU_CRL_LPF_GAIN, 0xa6);
		} else {
			stv0367_writereg(state, R367CAB_FSM_STATE, 0xa0);
			stv0367_writereg(state, R367CAB_EQU_CTR_LPF_GAIN, 0xd1);
			stv0367_writereg(state, R367CAB_EQU_CRL_LPF_GAIN, 0xa7);
		}
		stv0367_writereg(state, R367CAB_EQU_CRL_LD_SEN, 0x95);
		stv0367_writereg(state, R367CAB_EQU_CRL_LIMITER, 0x40);
		stv0367_writereg(state, R367CAB_EQU_PNT_GAIN, 0x99);
		break;
	case FE_CAB_MOD_QAM128:
		stv0367_writereg(state, R367CAB_IQDEM_ADJ_AGC_REF, 0x00);
		stv0367_writereg(state, R367CAB_AGC_PWR_REF_L, 0x76);
		stv0367_writereg(state, R367CAB_FSM_STATE, 0x90);
		stv0367_writereg(state, R367CAB_EQU_CTR_LPF_GAIN, 0xb1);
		if (SymbolRate > 4500000)
			stv0367_writereg(state, R367CAB_EQU_CRL_LPF_GAIN, 0xa7);
		else if (SymbolRate > 2500000)
			stv0367_writereg(state, R367CAB_EQU_CRL_LPF_GAIN, 0xa6);
		else
			stv0367_writereg(state, R367CAB_EQU_CRL_LPF_GAIN, 0x97);

		stv0367_writereg(state, R367CAB_EQU_CRL_LD_SEN, 0x8e);
		stv0367_writereg(state, R367CAB_EQU_CRL_LIMITER, 0x7f);
		stv0367_writereg(state, R367CAB_EQU_PNT_GAIN, 0xa7);
		break;
	case FE_CAB_MOD_QAM256:
		stv0367_writereg(state, R367CAB_IQDEM_ADJ_AGC_REF, 0x94);
		stv0367_writereg(state, R367CAB_AGC_PWR_REF_L, 0x5a);
		stv0367_writereg(state, R367CAB_FSM_STATE, 0xa0);
		if (SymbolRate > 4500000)
			stv0367_writereg(state, R367CAB_EQU_CTR_LPF_GAIN, 0xc1);
		else if (SymbolRate > 2500000)
			stv0367_writereg(state, R367CAB_EQU_CTR_LPF_GAIN, 0xc1);
		else
			stv0367_writereg(state, R367CAB_EQU_CTR_LPF_GAIN, 0xd1);

		stv0367_writereg(state, R367CAB_EQU_CRL_LPF_GAIN, 0xa7);
		stv0367_writereg(state, R367CAB_EQU_CRL_LD_SEN, 0x85);
		stv0367_writereg(state, R367CAB_EQU_CRL_LIMITER, 0x40);
		stv0367_writereg(state, R367CAB_EQU_PNT_GAIN, 0xa7);
		break;
	case FE_CAB_MOD_QAM512:
		stv0367_writereg(state, R367CAB_IQDEM_ADJ_AGC_REF, 0x00);
		break;
	case FE_CAB_MOD_QAM1024:
		stv0367_writereg(state, R367CAB_IQDEM_ADJ_AGC_REF, 0x00);
		break;
	default:
		break;
	}

	return QAMSize;
}