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
struct dib8000_state {int revision; } ;
typedef  enum dibx000_adc_states { ____Placeholder_dibx000_adc_states } dibx000_adc_states ;

/* Variables and functions */
#define  DIBX000_ADC_OFF 133 
#define  DIBX000_ADC_ON 132 
#define  DIBX000_SLOW_ADC_OFF 131 
#define  DIBX000_SLOW_ADC_ON 130 
#define  DIBX000_VBG_DISABLE 129 
#define  DIBX000_VBG_ENABLE 128 
 int dib8000_read_word (struct dib8000_state*,int) ; 
 int dib8000_write_word (struct dib8000_state*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int dib8000_set_adc_state(struct dib8000_state *state, enum dibx000_adc_states no)
{
	int ret = 0;
	u16 reg, reg_907 = dib8000_read_word(state, 907);
	u16 reg_908 = dib8000_read_word(state, 908);

	switch (no) {
	case DIBX000_SLOW_ADC_ON:
		if (state->revision != 0x8090) {
			reg_908 |= (1 << 1) | (1 << 0);
			ret |= dib8000_write_word(state, 908, reg_908);
			reg_908 &= ~(1 << 1);
		} else {
			reg = dib8000_read_word(state, 1925);
			/* en_slowAdc = 1 & reset_sladc = 1 */
			dib8000_write_word(state, 1925, reg |
					(1<<4) | (1<<2));

			/* read access to make it works... strange ... */
			reg = dib8000_read_word(state, 1925);
			msleep(20);
			/* en_slowAdc = 1 & reset_sladc = 0 */
			dib8000_write_word(state, 1925, reg & ~(1<<4));

			reg = dib8000_read_word(state, 921) & ~((0x3 << 14)
					| (0x3 << 12));
			/* ref = Vin1 => Vbg ; sel = Vin0 or Vin3 ;
			   (Vin2 = Vcm) */
			dib8000_write_word(state, 921, reg | (1 << 14)
					| (3 << 12));
		}
		break;

	case DIBX000_SLOW_ADC_OFF:
		if (state->revision == 0x8090) {
			reg = dib8000_read_word(state, 1925);
			/* reset_sladc = 1 en_slowAdc = 0 */
			dib8000_write_word(state, 1925,
					(reg & ~(1<<2)) | (1<<4));
		}
		reg_908 |= (1 << 1) | (1 << 0);
		break;

	case DIBX000_ADC_ON:
		reg_907 &= 0x0fff;
		reg_908 &= 0x0003;
		break;

	case DIBX000_ADC_OFF:	// leave the VBG voltage on
		reg_907 = (1 << 13) | (1 << 12);
		reg_908 = (1 << 6) | (1 << 5) | (1 << 4) | (1 << 3) | (1 << 1);
		break;

	case DIBX000_VBG_ENABLE:
		reg_907 &= ~(1 << 15);
		break;

	case DIBX000_VBG_DISABLE:
		reg_907 |= (1 << 15);
		break;

	default:
		break;
	}

	ret |= dib8000_write_word(state, 907, reg_907);
	ret |= dib8000_write_word(state, 908, reg_908);

	return ret;
}