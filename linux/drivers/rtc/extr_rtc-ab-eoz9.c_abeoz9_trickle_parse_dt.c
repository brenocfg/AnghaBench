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
typedef  int u32 ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ABEOZ9_REG_EEPROM_R1K ; 
 int ABEOZ9_REG_EEPROM_R20K ; 
 int ABEOZ9_REG_EEPROM_R5K ; 
 int ABEOZ9_REG_EEPROM_R80K ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static int abeoz9_trickle_parse_dt(struct device_node *node)
{
	u32 ohms = 0;

	if (of_property_read_u32(node, "trickle-resistor-ohms", &ohms))
		return 0;

	switch (ohms) {
	case 1000:
		return ABEOZ9_REG_EEPROM_R1K;
	case 5000:
		return ABEOZ9_REG_EEPROM_R5K;
	case 20000:
		return ABEOZ9_REG_EEPROM_R20K;
	case 80000:
		return ABEOZ9_REG_EEPROM_R80K;
	default:
		return 0;
	}
}