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
struct eeprom_93cx6 {int reg_data_in; int drive_data; int /*<<< orphan*/  (* register_write ) (struct eeprom_93cx6*) ;scalar_t__ reg_data_out; int /*<<< orphan*/  (* register_read ) (struct eeprom_93cx6*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  eeprom_93cx6_pulse_high (struct eeprom_93cx6*) ; 
 int /*<<< orphan*/  eeprom_93cx6_pulse_low (struct eeprom_93cx6*) ; 
 int /*<<< orphan*/  stub1 (struct eeprom_93cx6*) ; 
 int /*<<< orphan*/  stub2 (struct eeprom_93cx6*) ; 
 int /*<<< orphan*/  stub3 (struct eeprom_93cx6*) ; 

__attribute__((used)) static void eeprom_93cx6_write_bits(struct eeprom_93cx6 *eeprom,
	const u16 data, const u16 count)
{
	unsigned int i;

	eeprom->register_read(eeprom);

	/*
	 * Clear data flags.
	 */
	eeprom->reg_data_in = 0;
	eeprom->reg_data_out = 0;
	eeprom->drive_data = 1;

	/*
	 * Start writing all bits.
	 */
	for (i = count; i > 0; i--) {
		/*
		 * Check if this bit needs to be set.
		 */
		eeprom->reg_data_in = !!(data & (1 << (i - 1)));

		/*
		 * Write the bit to the eeprom register.
		 */
		eeprom->register_write(eeprom);

		/*
		 * Kick a pulse.
		 */
		eeprom_93cx6_pulse_high(eeprom);
		eeprom_93cx6_pulse_low(eeprom);
	}

	eeprom->reg_data_in = 0;
	eeprom->register_write(eeprom);
}