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
struct stv0367_state {int dummy; } ;
struct dvb_frontend {struct stv0367_state* demodulator_priv; } ;
typedef  enum stv0367cab_mod { ____Placeholder_stv0367cab_mod } stv0367cab_mod ;

/* Variables and functions */
 int /*<<< orphan*/  F367CAB_QAM_MODE ; 
#define  FE_CAB_MOD_QAM1024 134 
#define  FE_CAB_MOD_QAM128 133 
#define  FE_CAB_MOD_QAM16 132 
#define  FE_CAB_MOD_QAM256 131 
#define  FE_CAB_MOD_QAM32 130 
#define  FE_CAB_MOD_QAM4 129 
#define  FE_CAB_MOD_QAM64 128 
 int stv0367_readbits (struct stv0367_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stv0367cab_snr_power(struct dvb_frontend *fe)
{
	struct stv0367_state *state = fe->demodulator_priv;
	enum stv0367cab_mod QAMSize;

	QAMSize = stv0367_readbits(state, F367CAB_QAM_MODE);
	switch (QAMSize) {
	case FE_CAB_MOD_QAM4:
		return 21904;
	case FE_CAB_MOD_QAM16:
		return 20480;
	case FE_CAB_MOD_QAM32:
		return 23040;
	case FE_CAB_MOD_QAM64:
		return 21504;
	case FE_CAB_MOD_QAM128:
		return 23616;
	case FE_CAB_MOD_QAM256:
		return 21760;
	case FE_CAB_MOD_QAM1024:
		return 21280;
	default:
		break;
	}

	return 1;
}