#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct tm6000_input {int vmux; int amux; scalar_t__ type; int /*<<< orphan*/  v_gpio; } ;
struct tm6000_core {size_t input; scalar_t__ dev_type; int norm; struct tm6000_input rinput; struct tm6000_input* vinput; int /*<<< orphan*/  radio; } ;
struct TYPE_4__ {int id; int /*<<< orphan*/  common; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  REQ_03_SET_GET_MCU_PIN ; 
#define  TM6000_AMUX_ADC1 134 
#define  TM6000_AMUX_ADC2 133 
#define  TM6000_AMUX_SIF1 132 
#define  TM6000_AMUX_SIF2 131 
 scalar_t__ TM6000_INPUT_SVIDEO ; 
 int /*<<< orphan*/  TM6000_REQ07_RE3_VADC_INP_LPF_SEL1 ; 
 int /*<<< orphan*/  TM6000_REQ07_RE5_VADC_INP_LPF_SEL2 ; 
 int /*<<< orphan*/  TM6000_REQ07_RE8_VADC_PWDOWN_CTL ; 
 int /*<<< orphan*/  TM6000_REQ07_REB_VADC_AADC_MODE ; 
#define  TM6000_VMUX_VIDEO_A 130 
#define  TM6000_VMUX_VIDEO_AB 129 
#define  TM6000_VMUX_VIDEO_B 128 
 scalar_t__ TM6010 ; 
 int /*<<< orphan*/  TM6010_REQ07_R07_OUTPUT_CONTROL ; 
 int /*<<< orphan*/  TM6010_REQ07_RFE_POWER_DOWN ; 
 int /*<<< orphan*/  TM6010_REQ08_RE2_POWER_DOWN_CTRL1 ; 
 int /*<<< orphan*/  TM6010_REQ08_RE3_ADC_IN1_SEL ; 
 int /*<<< orphan*/  TM6010_REQ08_RE4_ADC_IN2_SEL ; 
 int /*<<< orphan*/  TM6010_REQ08_RE6_POWER_DOWN_CTRL2 ; 
 int /*<<< orphan*/  TM6010_REQ08_REA_BUFF_DRV_CTRL ; 
 int /*<<< orphan*/  TM6010_REQ08_REB_SIF_GAIN_CTRL ; 
 int /*<<< orphan*/  TM6010_REQ08_REC_REVERSE_YC_CTRL ; 
 int /*<<< orphan*/  TM6010_REQ08_RED_GAIN_SEL ; 
 int /*<<< orphan*/  TM6010_REQ08_RF0_DAUDIO_INPUT_CONFIG ; 
 int /*<<< orphan*/  TM6010_REQ08_RF1_AADC_POWER_DOWN ; 
 TYPE_1__* composite_stds ; 
 int /*<<< orphan*/  msleep (int) ; 
 TYPE_1__* svideo_stds ; 
 int /*<<< orphan*/  tm6000_get_std_res (struct tm6000_core*) ; 
 int tm6000_load_std (struct tm6000_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tm6000_set_audio_std (struct tm6000_core*) ; 
 int /*<<< orphan*/  tm6000_set_reg (struct tm6000_core*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  tm6000_set_reg_mask (struct tm6000_core*,int /*<<< orphan*/ ,int,int) ; 

int tm6000_set_standard(struct tm6000_core *dev)
{
	struct tm6000_input *input;
	int i, rc = 0;
	u8 reg_07_fe = 0x8a;
	u8 reg_08_f1 = 0xfc;
	u8 reg_08_e2 = 0xf0;
	u8 reg_08_e6 = 0x0f;

	tm6000_get_std_res(dev);

	if (!dev->radio)
		input = &dev->vinput[dev->input];
	else
		input = &dev->rinput;

	if (dev->dev_type == TM6010) {
		switch (input->vmux) {
		case TM6000_VMUX_VIDEO_A:
			tm6000_set_reg(dev, TM6010_REQ08_RE3_ADC_IN1_SEL, 0xf4);
			tm6000_set_reg(dev, TM6010_REQ08_REA_BUFF_DRV_CTRL, 0xf1);
			tm6000_set_reg(dev, TM6010_REQ08_REB_SIF_GAIN_CTRL, 0xe0);
			tm6000_set_reg(dev, TM6010_REQ08_REC_REVERSE_YC_CTRL, 0xc2);
			tm6000_set_reg(dev, TM6010_REQ08_RED_GAIN_SEL, 0xe8);
			reg_07_fe |= 0x01;
			break;
		case TM6000_VMUX_VIDEO_B:
			tm6000_set_reg(dev, TM6010_REQ08_RE3_ADC_IN1_SEL, 0xf8);
			tm6000_set_reg(dev, TM6010_REQ08_REA_BUFF_DRV_CTRL, 0xf1);
			tm6000_set_reg(dev, TM6010_REQ08_REB_SIF_GAIN_CTRL, 0xe0);
			tm6000_set_reg(dev, TM6010_REQ08_REC_REVERSE_YC_CTRL, 0xc2);
			tm6000_set_reg(dev, TM6010_REQ08_RED_GAIN_SEL, 0xe8);
			reg_07_fe |= 0x01;
			break;
		case TM6000_VMUX_VIDEO_AB:
			tm6000_set_reg(dev, TM6010_REQ08_RE3_ADC_IN1_SEL, 0xfc);
			tm6000_set_reg(dev, TM6010_REQ08_RE4_ADC_IN2_SEL, 0xf8);
			reg_08_e6 = 0x00;
			tm6000_set_reg(dev, TM6010_REQ08_REA_BUFF_DRV_CTRL, 0xf2);
			tm6000_set_reg(dev, TM6010_REQ08_REB_SIF_GAIN_CTRL, 0xf0);
			tm6000_set_reg(dev, TM6010_REQ08_REC_REVERSE_YC_CTRL, 0xc2);
			tm6000_set_reg(dev, TM6010_REQ08_RED_GAIN_SEL, 0xe0);
			break;
		default:
			break;
		}
		switch (input->amux) {
		case TM6000_AMUX_ADC1:
			tm6000_set_reg_mask(dev, TM6010_REQ08_RF0_DAUDIO_INPUT_CONFIG,
				0x00, 0x0f);
			/* Mux overflow workaround */
			tm6000_set_reg_mask(dev, TM6010_REQ07_R07_OUTPUT_CONTROL,
				0x10, 0xf0);
			break;
		case TM6000_AMUX_ADC2:
			tm6000_set_reg_mask(dev, TM6010_REQ08_RF0_DAUDIO_INPUT_CONFIG,
				0x08, 0x0f);
			/* Mux overflow workaround */
			tm6000_set_reg_mask(dev, TM6010_REQ07_R07_OUTPUT_CONTROL,
				0x10, 0xf0);
			break;
		case TM6000_AMUX_SIF1:
			reg_08_e2 |= 0x02;
			reg_08_e6 = 0x08;
			reg_07_fe |= 0x40;
			reg_08_f1 |= 0x02;
			tm6000_set_reg(dev, TM6010_REQ08_RE4_ADC_IN2_SEL, 0xf3);
			tm6000_set_reg_mask(dev, TM6010_REQ08_RF0_DAUDIO_INPUT_CONFIG,
				0x02, 0x0f);
			/* Mux overflow workaround */
			tm6000_set_reg_mask(dev, TM6010_REQ07_R07_OUTPUT_CONTROL,
				0x30, 0xf0);
			break;
		case TM6000_AMUX_SIF2:
			reg_08_e2 |= 0x02;
			reg_08_e6 = 0x08;
			reg_07_fe |= 0x40;
			reg_08_f1 |= 0x02;
			tm6000_set_reg(dev, TM6010_REQ08_RE4_ADC_IN2_SEL, 0xf7);
			tm6000_set_reg_mask(dev, TM6010_REQ08_RF0_DAUDIO_INPUT_CONFIG,
				0x02, 0x0f);
			/* Mux overflow workaround */
			tm6000_set_reg_mask(dev, TM6010_REQ07_R07_OUTPUT_CONTROL,
				0x30, 0xf0);
			break;
		default:
			break;
		}
		tm6000_set_reg(dev, TM6010_REQ08_RE2_POWER_DOWN_CTRL1, reg_08_e2);
		tm6000_set_reg(dev, TM6010_REQ08_RE6_POWER_DOWN_CTRL2, reg_08_e6);
		tm6000_set_reg(dev, TM6010_REQ08_RF1_AADC_POWER_DOWN, reg_08_f1);
		tm6000_set_reg(dev, TM6010_REQ07_RFE_POWER_DOWN, reg_07_fe);
	} else {
		switch (input->vmux) {
		case TM6000_VMUX_VIDEO_A:
			tm6000_set_reg(dev, TM6000_REQ07_RE3_VADC_INP_LPF_SEL1, 0x10);
			tm6000_set_reg(dev, TM6000_REQ07_RE5_VADC_INP_LPF_SEL2, 0x00);
			tm6000_set_reg(dev, TM6000_REQ07_RE8_VADC_PWDOWN_CTL, 0x0f);
			tm6000_set_reg(dev,
			    REQ_03_SET_GET_MCU_PIN, input->v_gpio, 0);
			break;
		case TM6000_VMUX_VIDEO_B:
			tm6000_set_reg(dev, TM6000_REQ07_RE3_VADC_INP_LPF_SEL1, 0x00);
			tm6000_set_reg(dev, TM6000_REQ07_RE5_VADC_INP_LPF_SEL2, 0x00);
			tm6000_set_reg(dev, TM6000_REQ07_RE8_VADC_PWDOWN_CTL, 0x0f);
			tm6000_set_reg(dev,
			    REQ_03_SET_GET_MCU_PIN, input->v_gpio, 0);
			break;
		case TM6000_VMUX_VIDEO_AB:
			tm6000_set_reg(dev, TM6000_REQ07_RE3_VADC_INP_LPF_SEL1, 0x10);
			tm6000_set_reg(dev, TM6000_REQ07_RE5_VADC_INP_LPF_SEL2, 0x10);
			tm6000_set_reg(dev, TM6000_REQ07_RE8_VADC_PWDOWN_CTL, 0x00);
			tm6000_set_reg(dev,
			    REQ_03_SET_GET_MCU_PIN, input->v_gpio, 1);
			break;
		default:
			break;
		}
		switch (input->amux) {
		case TM6000_AMUX_ADC1:
			tm6000_set_reg_mask(dev,
				TM6000_REQ07_REB_VADC_AADC_MODE, 0x00, 0x0f);
			break;
		case TM6000_AMUX_ADC2:
			tm6000_set_reg_mask(dev,
				TM6000_REQ07_REB_VADC_AADC_MODE, 0x04, 0x0f);
			break;
		default:
			break;
		}
	}
	if (input->type == TM6000_INPUT_SVIDEO) {
		for (i = 0; i < ARRAY_SIZE(svideo_stds); i++) {
			if (dev->norm & svideo_stds[i].id) {
				rc = tm6000_load_std(dev, svideo_stds[i].common);
				goto ret;
			}
		}
		return -EINVAL;
	} else {
		for (i = 0; i < ARRAY_SIZE(composite_stds); i++) {
			if (dev->norm & composite_stds[i].id) {
				rc = tm6000_load_std(dev, composite_stds[i].common);
				goto ret;
			}
		}
		return -EINVAL;
	}

ret:
	if (rc < 0)
		return rc;

	if ((dev->dev_type == TM6010) &&
	    ((input->amux == TM6000_AMUX_SIF1) ||
	    (input->amux == TM6000_AMUX_SIF2)))
		tm6000_set_audio_std(dev);

	msleep(40);

	return 0;
}