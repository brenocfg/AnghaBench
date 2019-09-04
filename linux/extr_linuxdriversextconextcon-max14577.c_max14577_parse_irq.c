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
struct max14577_muic_info {int irq_adc; int irq_chg; } ;

/* Variables and functions */
#define  MAX14577_IRQ_INT1_ADC 135 
#define  MAX14577_IRQ_INT1_ADCERR 134 
#define  MAX14577_IRQ_INT1_ADCLOW 133 
#define  MAX14577_IRQ_INT2_CHGDETRUN 132 
#define  MAX14577_IRQ_INT2_CHGTYP 131 
#define  MAX14577_IRQ_INT2_DBCHG 130 
#define  MAX14577_IRQ_INT2_DCDTMR 129 
#define  MAX14577_IRQ_INT2_VBVOLT 128 

__attribute__((used)) static int max14577_parse_irq(struct max14577_muic_info *info, int irq_type)
{
	switch (irq_type) {
	case MAX14577_IRQ_INT1_ADC:
	case MAX14577_IRQ_INT1_ADCLOW:
	case MAX14577_IRQ_INT1_ADCERR:
		/*
		 * Handle all of accessory except for
		 * type of charger accessory.
		 */
		info->irq_adc = true;
		return 1;
	case MAX14577_IRQ_INT2_CHGTYP:
	case MAX14577_IRQ_INT2_CHGDETRUN:
	case MAX14577_IRQ_INT2_DCDTMR:
	case MAX14577_IRQ_INT2_DBCHG:
	case MAX14577_IRQ_INT2_VBVOLT:
		/* Handle charger accessory */
		info->irq_chg = true;
		return 1;
	default:
		return 0;
	}
}