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
struct eeprom_93cx6 {scalar_t__ reg_data_out; scalar_t__ reg_data_in; int /*<<< orphan*/  (* register_read ) (struct eeprom_93cx6*) ;scalar_t__ drive_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  eeprom_93cx6_pulse_high (struct eeprom_93cx6*) ; 
 int /*<<< orphan*/  eeprom_93cx6_pulse_low (struct eeprom_93cx6*) ; 
 int /*<<< orphan*/  stub1 (struct eeprom_93cx6*) ; 
 int /*<<< orphan*/  stub2 (struct eeprom_93cx6*) ; 

__attribute__((used)) static void eeprom_93cx6_read_bits(struct eeprom_93cx6 *eeprom,
	u16 *data, const u16 count)
{
	unsigned int i;
	u16 buf = 0;

	eeprom->register_read(eeprom);

	/*
	 * Clear data flags.
	 */
	eeprom->reg_data_in = 0;
	eeprom->reg_data_out = 0;
	eeprom->drive_data = 0;

	/*
	 * Start reading all bits.
	 */
	for (i = count; i > 0; i--) {
		eeprom_93cx6_pulse_high(eeprom);

		eeprom->register_read(eeprom);

		/*
		 * Clear data_in flag.
		 */
		eeprom->reg_data_in = 0;

		/*
		 * Read if the bit has been set.
		 */
		if (eeprom->reg_data_out)
			buf |= (1 << (i - 1));

		eeprom_93cx6_pulse_low(eeprom);
	}

	*data = buf;
}