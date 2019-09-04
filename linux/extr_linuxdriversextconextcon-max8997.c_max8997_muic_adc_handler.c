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
struct max8997_muic_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  edev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  EXTCON_DISP_MHL ; 
 int /*<<< orphan*/  MAX8997_CABLE_GROUP_ADC ; 
#define  MAX8997_MUIC_ADC_AUDIO_MODE_REMOTE 158 
#define  MAX8997_MUIC_ADC_AV_CABLE_NOLOAD 157 
#define  MAX8997_MUIC_ADC_CEA936A_TYPE1_CHG 156 
#define  MAX8997_MUIC_ADC_CEA936A_TYPE2_CHG 155 
#define  MAX8997_MUIC_ADC_CEA936_AUDIO 154 
#define  MAX8997_MUIC_ADC_FACTORY_MODE_UART_OFF 153 
#define  MAX8997_MUIC_ADC_FACTORY_MODE_UART_ON 152 
#define  MAX8997_MUIC_ADC_FACTORY_MODE_USB_OFF 151 
#define  MAX8997_MUIC_ADC_FACTORY_MODE_USB_ON 150 
#define  MAX8997_MUIC_ADC_GROUND 149 
#define  MAX8997_MUIC_ADC_MHL 148 
#define  MAX8997_MUIC_ADC_PHONE_POWERED_DEV 147 
#define  MAX8997_MUIC_ADC_REMOTE_S10_BUTTON 146 
#define  MAX8997_MUIC_ADC_REMOTE_S11_BUTTON 145 
#define  MAX8997_MUIC_ADC_REMOTE_S12_BUTTON 144 
#define  MAX8997_MUIC_ADC_REMOTE_S1_BUTTON 143 
#define  MAX8997_MUIC_ADC_REMOTE_S2_BUTTON 142 
#define  MAX8997_MUIC_ADC_REMOTE_S3_BUTTON 141 
#define  MAX8997_MUIC_ADC_REMOTE_S4_BUTTON 140 
#define  MAX8997_MUIC_ADC_REMOTE_S5_BUTTON 139 
#define  MAX8997_MUIC_ADC_REMOTE_S6_BUTTON 138 
#define  MAX8997_MUIC_ADC_REMOTE_S7_BUTTON 137 
#define  MAX8997_MUIC_ADC_REMOTE_S8_BUTTON 136 
#define  MAX8997_MUIC_ADC_REMOTE_S9_BUTTON 135 
#define  MAX8997_MUIC_ADC_RESERVED_ACC_1 134 
#define  MAX8997_MUIC_ADC_RESERVED_ACC_2 133 
#define  MAX8997_MUIC_ADC_RESERVED_ACC_3 132 
#define  MAX8997_MUIC_ADC_RESERVED_ACC_4 131 
#define  MAX8997_MUIC_ADC_RESERVED_ACC_5 130 
#define  MAX8997_MUIC_ADC_TTY_CONVERTER 129 
#define  MAX8997_MUIC_ADC_UART_CABLE 128 
 int /*<<< orphan*/  MAX8997_USB_DEVICE ; 
 int /*<<< orphan*/  MAX8997_USB_HOST ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  extcon_set_state_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int max8997_muic_get_cable_type (struct max8997_muic_info*,int /*<<< orphan*/ ,int*) ; 
 int max8997_muic_handle_dock (struct max8997_muic_info*,int,int) ; 
 int max8997_muic_handle_jig_uart (struct max8997_muic_info*,int) ; 
 int max8997_muic_handle_usb (struct max8997_muic_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max8997_muic_adc_handler(struct max8997_muic_info *info)
{
	int cable_type;
	bool attached;
	int ret = 0;

	/* Check cable state which is either detached or attached */
	cable_type = max8997_muic_get_cable_type(info,
				MAX8997_CABLE_GROUP_ADC, &attached);

	switch (cable_type) {
	case MAX8997_MUIC_ADC_GROUND:
		ret = max8997_muic_handle_usb(info, MAX8997_USB_HOST, attached);
		if (ret < 0)
			return ret;
		break;
	case MAX8997_MUIC_ADC_MHL:
		extcon_set_state_sync(info->edev, EXTCON_DISP_MHL, attached);
		break;
	case MAX8997_MUIC_ADC_FACTORY_MODE_USB_OFF:
	case MAX8997_MUIC_ADC_FACTORY_MODE_USB_ON:
		ret = max8997_muic_handle_usb(info,
					     MAX8997_USB_DEVICE, attached);
		if (ret < 0)
			return ret;
		break;
	case MAX8997_MUIC_ADC_AV_CABLE_NOLOAD:
	case MAX8997_MUIC_ADC_FACTORY_MODE_UART_ON:
		ret = max8997_muic_handle_dock(info, cable_type, attached);
		if (ret < 0)
			return ret;
		break;
	case MAX8997_MUIC_ADC_FACTORY_MODE_UART_OFF:
		ret = max8997_muic_handle_jig_uart(info, attached);
		break;
	case MAX8997_MUIC_ADC_REMOTE_S1_BUTTON:
	case MAX8997_MUIC_ADC_REMOTE_S2_BUTTON:
	case MAX8997_MUIC_ADC_REMOTE_S3_BUTTON:
	case MAX8997_MUIC_ADC_REMOTE_S4_BUTTON:
	case MAX8997_MUIC_ADC_REMOTE_S5_BUTTON:
	case MAX8997_MUIC_ADC_REMOTE_S6_BUTTON:
	case MAX8997_MUIC_ADC_REMOTE_S7_BUTTON:
	case MAX8997_MUIC_ADC_REMOTE_S8_BUTTON:
	case MAX8997_MUIC_ADC_REMOTE_S9_BUTTON:
	case MAX8997_MUIC_ADC_REMOTE_S10_BUTTON:
	case MAX8997_MUIC_ADC_REMOTE_S11_BUTTON:
	case MAX8997_MUIC_ADC_REMOTE_S12_BUTTON:
	case MAX8997_MUIC_ADC_RESERVED_ACC_1:
	case MAX8997_MUIC_ADC_RESERVED_ACC_2:
	case MAX8997_MUIC_ADC_RESERVED_ACC_3:
	case MAX8997_MUIC_ADC_RESERVED_ACC_4:
	case MAX8997_MUIC_ADC_RESERVED_ACC_5:
	case MAX8997_MUIC_ADC_CEA936_AUDIO:
	case MAX8997_MUIC_ADC_PHONE_POWERED_DEV:
	case MAX8997_MUIC_ADC_TTY_CONVERTER:
	case MAX8997_MUIC_ADC_UART_CABLE:
	case MAX8997_MUIC_ADC_CEA936A_TYPE1_CHG:
	case MAX8997_MUIC_ADC_CEA936A_TYPE2_CHG:
	case MAX8997_MUIC_ADC_AUDIO_MODE_REMOTE:
		/*
		 * This cable isn't used in general case if it is specially
		 * needed to detect additional cable, should implement
		 * proper operation when this cable is attached/detached.
		 */
		dev_info(info->dev,
			"cable is %s but it isn't used (type:0x%x)\n",
			attached ? "attached" : "detached", cable_type);
		return -EAGAIN;
	default:
		dev_err(info->dev,
			"failed to detect %s unknown cable (type:0x%x)\n",
			attached ? "attached" : "detached", cable_type);
		return -EINVAL;
	}

	return 0;
}