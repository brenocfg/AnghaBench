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
typedef  int /*<<< orphan*/  u8 ;
struct mantis_pci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANTIS_ERROR ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,int) ; 
 int read_eeprom_bytes (struct mantis_pci*,int,int /*<<< orphan*/ *,int) ; 

int mantis_get_mac(struct mantis_pci *mantis)
{
	int err;
	u8 mac_addr[6] = {0};

	err = read_eeprom_bytes(mantis, 0x08, mac_addr, 6);
	if (err < 0) {
		dprintk(MANTIS_ERROR, 1, "ERROR: Mantis EEPROM read error <%d>", err);

		return err;
	}

	dprintk(MANTIS_ERROR, 0, "    MAC Address=[%pM]\n", mac_addr);

	return 0;
}