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
struct TYPE_2__ {int disable_sample_and_hold; int enable_current_mirror; } ;
struct dib7000p_state {scalar_t__ version; TYPE_1__ cfg; } ;
typedef  enum dibx000_adc_states { ____Placeholder_dibx000_adc_states } dibx000_adc_states ;

/* Variables and functions */
#define  DIBX000_ADC_OFF 133 
#define  DIBX000_ADC_ON 132 
#define  DIBX000_SLOW_ADC_OFF 131 
#define  DIBX000_SLOW_ADC_ON 130 
#define  DIBX000_VBG_DISABLE 129 
#define  DIBX000_VBG_ENABLE 128 
 scalar_t__ SOC7090 ; 
 int dib7000p_read_word (struct dib7000p_state*,int) ; 
 int /*<<< orphan*/  dib7000p_write_word (struct dib7000p_state*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void dib7000p_set_adc_state(struct dib7000p_state *state, enum dibx000_adc_states no)
{
	u16 reg_908 = 0, reg_909 = 0;
	u16 reg;

	if (state->version != SOC7090) {
		reg_908 = dib7000p_read_word(state, 908);
		reg_909 = dib7000p_read_word(state, 909);
	}

	switch (no) {
	case DIBX000_SLOW_ADC_ON:
		if (state->version == SOC7090) {
			reg = dib7000p_read_word(state, 1925);

			dib7000p_write_word(state, 1925, reg | (1 << 4) | (1 << 2));	/* en_slowAdc = 1 & reset_sladc = 1 */

			reg = dib7000p_read_word(state, 1925);	/* read access to make it works... strange ... */
			msleep(200);
			dib7000p_write_word(state, 1925, reg & ~(1 << 4));	/* en_slowAdc = 1 & reset_sladc = 0 */

			reg = dib7000p_read_word(state, 72) & ~((0x3 << 14) | (0x3 << 12));
			dib7000p_write_word(state, 72, reg | (1 << 14) | (3 << 12) | 524);	/* ref = Vin1 => Vbg ; sel = Vin0 or Vin3 ; (Vin2 = Vcm) */
		} else {
			reg_909 |= (1 << 1) | (1 << 0);
			dib7000p_write_word(state, 909, reg_909);
			reg_909 &= ~(1 << 1);
		}
		break;

	case DIBX000_SLOW_ADC_OFF:
		if (state->version == SOC7090) {
			reg = dib7000p_read_word(state, 1925);
			dib7000p_write_word(state, 1925, (reg & ~(1 << 2)) | (1 << 4));	/* reset_sladc = 1 en_slowAdc = 0 */
		} else
			reg_909 |= (1 << 1) | (1 << 0);
		break;

	case DIBX000_ADC_ON:
		reg_908 &= 0x0fff;
		reg_909 &= 0x0003;
		break;

	case DIBX000_ADC_OFF:
		reg_908 |= (1 << 14) | (1 << 13) | (1 << 12);
		reg_909 |= (1 << 5) | (1 << 4) | (1 << 3) | (1 << 2);
		break;

	case DIBX000_VBG_ENABLE:
		reg_908 &= ~(1 << 15);
		break;

	case DIBX000_VBG_DISABLE:
		reg_908 |= (1 << 15);
		break;

	default:
		break;
	}

//	dprintk( "908: %x, 909: %x\n", reg_908, reg_909);

	reg_909 |= (state->cfg.disable_sample_and_hold & 1) << 4;
	reg_908 |= (state->cfg.enable_current_mirror & 1) << 7;

	if (state->version != SOC7090) {
		dib7000p_write_word(state, 908, reg_908);
		dib7000p_write_word(state, 909, reg_909);
	}
}