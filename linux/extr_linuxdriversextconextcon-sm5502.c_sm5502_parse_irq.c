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
struct sm5502_muic_info {int irq_attach; int irq_detach; } ;

/* Variables and functions */
#define  SM5502_IRQ_INT1_ATTACH 141 
#define  SM5502_IRQ_INT1_DETACH 140 
#define  SM5502_IRQ_INT1_KP 139 
#define  SM5502_IRQ_INT1_LKP 138 
#define  SM5502_IRQ_INT1_LKR 137 
#define  SM5502_IRQ_INT1_OCP_EVENT 136 
#define  SM5502_IRQ_INT1_OVP_EVENT 135 
#define  SM5502_IRQ_INT1_OVP_OCP_DIS 134 
#define  SM5502_IRQ_INT2_ADC_CHG 133 
#define  SM5502_IRQ_INT2_MHL 132 
#define  SM5502_IRQ_INT2_REV_ACCE 131 
#define  SM5502_IRQ_INT2_STUCK_KEY 130 
#define  SM5502_IRQ_INT2_STUCK_KEY_RCV 129 
#define  SM5502_IRQ_INT2_VBUS_DET 128 

__attribute__((used)) static int sm5502_parse_irq(struct sm5502_muic_info *info, int irq_type)
{
	switch (irq_type) {
	case SM5502_IRQ_INT1_ATTACH:
		info->irq_attach = true;
		break;
	case SM5502_IRQ_INT1_DETACH:
		info->irq_detach = true;
		break;
	case SM5502_IRQ_INT1_KP:
	case SM5502_IRQ_INT1_LKP:
	case SM5502_IRQ_INT1_LKR:
	case SM5502_IRQ_INT1_OVP_EVENT:
	case SM5502_IRQ_INT1_OCP_EVENT:
	case SM5502_IRQ_INT1_OVP_OCP_DIS:
	case SM5502_IRQ_INT2_VBUS_DET:
	case SM5502_IRQ_INT2_REV_ACCE:
	case SM5502_IRQ_INT2_ADC_CHG:
	case SM5502_IRQ_INT2_STUCK_KEY:
	case SM5502_IRQ_INT2_STUCK_KEY_RCV:
	case SM5502_IRQ_INT2_MHL:
	default:
		break;
	}

	return 0;
}