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
struct i2c_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  encodedMAC ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ *) ; 
 int getmac_tt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int ttpci_eeprom_read_encodedMAC (struct i2c_adapter*,int /*<<< orphan*/ *) ; 

int ttpci_eeprom_parse_mac(struct i2c_adapter *adapter, u8 *proposed_mac)
{
	int ret;
	u8 encodedMAC[20];
	u8 decodedMAC[6];

	ret = ttpci_eeprom_read_encodedMAC(adapter, encodedMAC);

	if (ret != 0) {		/* Will only be -ENODEV */
		dprintk("Couldn't read from EEPROM: not there?\n");
		eth_zero_addr(proposed_mac);
		return ret;
	}

	ret = getmac_tt(decodedMAC, encodedMAC);
	if( ret != 0 ) {
		dprintk("adapter failed MAC signature check\n");
		dprintk("encoded MAC from EEPROM was %*phC",
			(int)sizeof(encodedMAC), &encodedMAC);
		eth_zero_addr(proposed_mac);
		return ret;
	}

	memcpy(proposed_mac, decodedMAC, 6);
	dprintk("adapter has MAC addr = %pM\n", decodedMAC);
	return 0;
}