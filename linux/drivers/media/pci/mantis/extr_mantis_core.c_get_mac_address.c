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
struct mantis_pci {int* mac_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANTIS_ERROR ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 int read_eeprom_byte (struct mantis_pci*,int*,int) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int get_mac_address(struct mantis_pci *mantis)
{
	int err;

	mantis->mac_address[0] = 0x08;
	err = read_eeprom_byte(mantis, &mantis->mac_address[0], 6);
	if (err < 0) {
		dprintk(verbose, MANTIS_ERROR, 1, "Mantis EEPROM read error");

		return err;
	}
	dprintk(verbose, MANTIS_ERROR, 0,
		"    MAC Address=[%pM]\n", mantis->mac_address);

	return 0;
}