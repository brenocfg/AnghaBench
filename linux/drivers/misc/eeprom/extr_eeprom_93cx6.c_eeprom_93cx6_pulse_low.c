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
struct eeprom_93cx6 {int /*<<< orphan*/  (* register_write ) (struct eeprom_93cx6*) ;scalar_t__ reg_data_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ndelay (int) ; 
 int /*<<< orphan*/  stub1 (struct eeprom_93cx6*) ; 

__attribute__((used)) static inline void eeprom_93cx6_pulse_low(struct eeprom_93cx6 *eeprom)
{
	eeprom->reg_data_clock = 0;
	eeprom->register_write(eeprom);

	/*
	 * Add a short delay for the pulse to work.
	 * According to the specifications the "maximum minimum"
	 * time should be 450ns.
	 */
	ndelay(450);
}