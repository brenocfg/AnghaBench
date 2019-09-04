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
struct sm5502_muic_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int EINVAL ; 
#define  SM5502_MUIC_ADC_AUDIO_TYPE1 162 
#define  SM5502_MUIC_ADC_AUDIO_TYPE2 161 
#define  SM5502_MUIC_ADC_AUDIO_VIDEO_CABLE 160 
#define  SM5502_MUIC_ADC_FACTORY_MODE_BOOT_OFF_UART 159 
#define  SM5502_MUIC_ADC_FACTORY_MODE_BOOT_OFF_USB 158 
#define  SM5502_MUIC_ADC_FACTORY_MODE_BOOT_ON_UART 157 
#define  SM5502_MUIC_ADC_FACTORY_MODE_BOOT_ON_USB 156 
#define  SM5502_MUIC_ADC_GROUND 155 
#define  SM5502_MUIC_ADC_OPEN 154 
 unsigned int SM5502_MUIC_ADC_OPEN_TA ; 
 unsigned int SM5502_MUIC_ADC_OPEN_USB ; 
 unsigned int SM5502_MUIC_ADC_OPEN_USB_OTG ; 
#define  SM5502_MUIC_ADC_PHONE_POWERED_DEV 153 
#define  SM5502_MUIC_ADC_REMOTE_S10_BUTTON 152 
#define  SM5502_MUIC_ADC_REMOTE_S11_BUTTON 151 
#define  SM5502_MUIC_ADC_REMOTE_S12_BUTTON 150 
#define  SM5502_MUIC_ADC_REMOTE_S1_BUTTON 149 
#define  SM5502_MUIC_ADC_REMOTE_S2_BUTTON 148 
#define  SM5502_MUIC_ADC_REMOTE_S3_BUTTON 147 
#define  SM5502_MUIC_ADC_REMOTE_S4_BUTTON 146 
#define  SM5502_MUIC_ADC_REMOTE_S5_BUTTON 145 
#define  SM5502_MUIC_ADC_REMOTE_S6_BUTTON 144 
#define  SM5502_MUIC_ADC_REMOTE_S7_BUTTON 143 
#define  SM5502_MUIC_ADC_REMOTE_S8_BUTTON 142 
#define  SM5502_MUIC_ADC_REMOTE_S9_BUTTON 141 
#define  SM5502_MUIC_ADC_RESERVED_ACC_1 140 
#define  SM5502_MUIC_ADC_RESERVED_ACC_2 139 
#define  SM5502_MUIC_ADC_RESERVED_ACC_3 138 
#define  SM5502_MUIC_ADC_RESERVED_ACC_4 137 
#define  SM5502_MUIC_ADC_RESERVED_ACC_5 136 
#define  SM5502_MUIC_ADC_SEND_END_BUTTON 135 
#define  SM5502_MUIC_ADC_TTY_CONVERTER 134 
#define  SM5502_MUIC_ADC_TYPE1_CHARGER 133 
#define  SM5502_MUIC_ADC_TYPE2_CHARGER 132 
#define  SM5502_MUIC_ADC_UART_CABLE 131 
 int /*<<< orphan*/  SM5502_REG_ADC ; 
 unsigned int SM5502_REG_ADC_MASK ; 
 int /*<<< orphan*/  SM5502_REG_DEV_TYPE1 ; 
#define  SM5502_REG_DEV_TYPE1_DEDICATED_CHG_MASK 130 
#define  SM5502_REG_DEV_TYPE1_USB_OTG_MASK 129 
#define  SM5502_REG_DEV_TYPE1_USB_SDP_MASK 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static unsigned int sm5502_muic_get_cable_type(struct sm5502_muic_info *info)
{
	unsigned int cable_type = -1, adc, dev_type1;
	int ret;

	/* Read ADC value according to external cable or button */
	ret = regmap_read(info->regmap, SM5502_REG_ADC, &adc);
	if (ret) {
		dev_err(info->dev, "failed to read ADC register\n");
		return ret;
	}

	/*
	 * If ADC is SM5502_MUIC_ADC_GROUND(0x0), external cable hasn't
	 * connected with to MUIC device.
	 */
	cable_type = adc & SM5502_REG_ADC_MASK;
	if (cable_type == SM5502_MUIC_ADC_GROUND)
		return SM5502_MUIC_ADC_GROUND;

	switch (cable_type) {
	case SM5502_MUIC_ADC_GROUND:
	case SM5502_MUIC_ADC_SEND_END_BUTTON:
	case SM5502_MUIC_ADC_REMOTE_S1_BUTTON:
	case SM5502_MUIC_ADC_REMOTE_S2_BUTTON:
	case SM5502_MUIC_ADC_REMOTE_S3_BUTTON:
	case SM5502_MUIC_ADC_REMOTE_S4_BUTTON:
	case SM5502_MUIC_ADC_REMOTE_S5_BUTTON:
	case SM5502_MUIC_ADC_REMOTE_S6_BUTTON:
	case SM5502_MUIC_ADC_REMOTE_S7_BUTTON:
	case SM5502_MUIC_ADC_REMOTE_S8_BUTTON:
	case SM5502_MUIC_ADC_REMOTE_S9_BUTTON:
	case SM5502_MUIC_ADC_REMOTE_S10_BUTTON:
	case SM5502_MUIC_ADC_REMOTE_S11_BUTTON:
	case SM5502_MUIC_ADC_REMOTE_S12_BUTTON:
	case SM5502_MUIC_ADC_RESERVED_ACC_1:
	case SM5502_MUIC_ADC_RESERVED_ACC_2:
	case SM5502_MUIC_ADC_RESERVED_ACC_3:
	case SM5502_MUIC_ADC_RESERVED_ACC_4:
	case SM5502_MUIC_ADC_RESERVED_ACC_5:
	case SM5502_MUIC_ADC_AUDIO_TYPE2:
	case SM5502_MUIC_ADC_PHONE_POWERED_DEV:
	case SM5502_MUIC_ADC_TTY_CONVERTER:
	case SM5502_MUIC_ADC_UART_CABLE:
	case SM5502_MUIC_ADC_TYPE1_CHARGER:
	case SM5502_MUIC_ADC_FACTORY_MODE_BOOT_OFF_USB:
	case SM5502_MUIC_ADC_FACTORY_MODE_BOOT_ON_USB:
	case SM5502_MUIC_ADC_AUDIO_VIDEO_CABLE:
	case SM5502_MUIC_ADC_TYPE2_CHARGER:
	case SM5502_MUIC_ADC_FACTORY_MODE_BOOT_OFF_UART:
	case SM5502_MUIC_ADC_FACTORY_MODE_BOOT_ON_UART:
		break;
	case SM5502_MUIC_ADC_AUDIO_TYPE1:
		/*
		 * Check whether cable type is
		 * SM5502_MUIC_ADC_AUDIO_TYPE1_FULL_REMOTE
		 * or SM5502_MUIC_ADC_AUDIO_TYPE1_SEND_END
		 * by using Button event.
		 */
		break;
	case SM5502_MUIC_ADC_OPEN:
		ret = regmap_read(info->regmap, SM5502_REG_DEV_TYPE1,
				  &dev_type1);
		if (ret) {
			dev_err(info->dev, "failed to read DEV_TYPE1 reg\n");
			return ret;
		}

		switch (dev_type1) {
		case SM5502_REG_DEV_TYPE1_USB_SDP_MASK:
			cable_type = SM5502_MUIC_ADC_OPEN_USB;
			break;
		case SM5502_REG_DEV_TYPE1_DEDICATED_CHG_MASK:
			cable_type = SM5502_MUIC_ADC_OPEN_TA;
			break;
		case SM5502_REG_DEV_TYPE1_USB_OTG_MASK:
			cable_type = SM5502_MUIC_ADC_OPEN_USB_OTG;
			break;
		default:
			dev_dbg(info->dev,
				"cannot identify the cable type: adc(0x%x)\n",
				adc);
			return -EINVAL;
		};
		break;
	default:
		dev_err(info->dev,
			"failed to identify the cable type: adc(0x%x)\n", adc);
		return -EINVAL;
	};

	return cable_type;
}