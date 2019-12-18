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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct cx231xx {int afe_ref_count; scalar_t__ video_input; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_INPUT_CH1 ; 
 int /*<<< orphan*/  ADC_INPUT_CH3 ; 
 int /*<<< orphan*/  ADC_NTF_PRECLMP_EN_CH1 ; 
 int /*<<< orphan*/  ADC_NTF_PRECLMP_EN_CH3 ; 
 scalar_t__ CX231XX_VMUX_TELEVISION ; 
#define  EU_IF 131 
#define  LOW_IF 130 
#define  SINGLE_ENDED 129 
#define  US_IF 128 
 int afe_read_byte (struct cx231xx*,int /*<<< orphan*/ ,int*) ; 
 int cx231xx_afe_init_super_block (struct cx231xx*,int) ; 

int cx231xx_afe_adjust_ref_count(struct cx231xx *dev, u32 video_input)
{
	u8 input_mode = 0;
	u8 ntf_mode = 0;
	int status = 0;

	dev->video_input = video_input;

	if (video_input == CX231XX_VMUX_TELEVISION) {
		status = afe_read_byte(dev, ADC_INPUT_CH3, &input_mode);
		status = afe_read_byte(dev, ADC_NTF_PRECLMP_EN_CH3,
					&ntf_mode);
	} else {
		status = afe_read_byte(dev, ADC_INPUT_CH1, &input_mode);
		status = afe_read_byte(dev, ADC_NTF_PRECLMP_EN_CH1,
					&ntf_mode);
	}

	input_mode = (ntf_mode & 0x3) | ((input_mode & 0x6) << 1);

	switch (input_mode) {
	case SINGLE_ENDED:
		dev->afe_ref_count = 0x23C;
		break;
	case LOW_IF:
		dev->afe_ref_count = 0x24C;
		break;
	case EU_IF:
		dev->afe_ref_count = 0x258;
		break;
	case US_IF:
		dev->afe_ref_count = 0x260;
		break;
	default:
		break;
	}

	status = cx231xx_afe_init_super_block(dev, dev->afe_ref_count);

	return status;
}