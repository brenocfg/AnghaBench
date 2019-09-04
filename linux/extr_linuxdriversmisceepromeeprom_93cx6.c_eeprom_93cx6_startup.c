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
struct eeprom_93cx6 {int reg_chip_select; int drive_data; int /*<<< orphan*/  (* register_write ) (struct eeprom_93cx6*) ;scalar_t__ reg_data_clock; scalar_t__ reg_data_out; scalar_t__ reg_data_in; int /*<<< orphan*/  (* register_read ) (struct eeprom_93cx6*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  eeprom_93cx6_pulse_high (struct eeprom_93cx6*) ; 
 int /*<<< orphan*/  eeprom_93cx6_pulse_low (struct eeprom_93cx6*) ; 
 int /*<<< orphan*/  stub1 (struct eeprom_93cx6*) ; 
 int /*<<< orphan*/  stub2 (struct eeprom_93cx6*) ; 

__attribute__((used)) static void eeprom_93cx6_startup(struct eeprom_93cx6 *eeprom)
{
	/*
	 * Clear all flags, and enable chip select.
	 */
	eeprom->register_read(eeprom);
	eeprom->reg_data_in = 0;
	eeprom->reg_data_out = 0;
	eeprom->reg_data_clock = 0;
	eeprom->reg_chip_select = 1;
	eeprom->drive_data = 1;
	eeprom->register_write(eeprom);

	/*
	 * kick a pulse.
	 */
	eeprom_93cx6_pulse_high(eeprom);
	eeprom_93cx6_pulse_low(eeprom);
}