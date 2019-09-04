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
typedef  int u32 ;
struct tda_state {int /*<<< orphan*/  m_SettlingTime; int /*<<< orphan*/  m_Frequency; } ;
struct TYPE_2__ {int bandwidth_hz; int delivery_system; int /*<<< orphan*/  frequency; } ;
struct dvb_frontend {TYPE_1__ dtv_property_cache; struct tda_state* tuner_priv; } ;

/* Variables and functions */
 int ChannelConfiguration (struct tda_state*,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int HF_DVBC_6MHZ ; 
 int HF_DVBC_7MHZ ; 
 int HF_DVBC_8MHZ ; 
 int HF_DVBT_6MHZ ; 
 int HF_DVBT_7MHZ ; 
 int HF_DVBT_8MHZ ; 
 int RFTrackingFiltersCorrection (struct tda_state*,int /*<<< orphan*/ ) ; 
#define  SYS_DVBC_ANNEX_A 131 
#define  SYS_DVBC_ANNEX_C 130 
#define  SYS_DVBT 129 
#define  SYS_DVBT2 128 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_params(struct dvb_frontend *fe)
{
	struct tda_state *state = fe->tuner_priv;
	int status = 0;
	int Standard;
	u32 bw = fe->dtv_property_cache.bandwidth_hz;
	u32 delsys  = fe->dtv_property_cache.delivery_system;

	state->m_Frequency = fe->dtv_property_cache.frequency;

	switch (delsys) {
	case  SYS_DVBT:
	case  SYS_DVBT2:
		switch (bw) {
		case 6000000:
			Standard = HF_DVBT_6MHZ;
			break;
		case 7000000:
			Standard = HF_DVBT_7MHZ;
			break;
		case 8000000:
			Standard = HF_DVBT_8MHZ;
			break;
		default:
			return -EINVAL;
		}
		break;
	case SYS_DVBC_ANNEX_A:
	case SYS_DVBC_ANNEX_C:
		if (bw <= 6000000)
			Standard = HF_DVBC_6MHZ;
		else if (bw <= 7000000)
			Standard = HF_DVBC_7MHZ;
		else
			Standard = HF_DVBC_8MHZ;
		break;
	default:
		return -EINVAL;
	}
	do {
		status = RFTrackingFiltersCorrection(state, state->m_Frequency);
		if (status < 0)
			break;
		status = ChannelConfiguration(state, state->m_Frequency,
					      Standard);
		if (status < 0)
			break;

		msleep(state->m_SettlingTime);  /* Allow AGC's to settle down */
	} while (0);
	return status;
}