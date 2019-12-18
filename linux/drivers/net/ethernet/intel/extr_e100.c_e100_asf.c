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
struct nic {int* eeprom; TYPE_1__* pdev; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
 int eeprom_asf ; 
 size_t eeprom_config_asf ; 
 int eeprom_gcl ; 
 size_t eeprom_smbus_addr ; 

__attribute__((used)) static int e100_asf(struct nic *nic)
{
	/* ASF can be enabled from eeprom */
	return (nic->pdev->device >= 0x1050) && (nic->pdev->device <= 0x1057) &&
	   (nic->eeprom[eeprom_config_asf] & eeprom_asf) &&
	   !(nic->eeprom[eeprom_config_asf] & eeprom_gcl) &&
	   ((nic->eeprom[eeprom_smbus_addr] & 0xFF) != 0xFE);
}