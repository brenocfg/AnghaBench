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
typedef  int u8 ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_mutex; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  I2C_ADDR_24C16 ; 
 int /*<<< orphan*/  I2C_ADDR_24C64 ; 
 int /*<<< orphan*/  eth_zero_addr (int*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pctv452e_i2c_msg (struct dvb_usb_device*,int /*<<< orphan*/ ,int const*,int,int*,int) ; 
 int ttpci_eeprom_decode_mac (int*,int*) ; 

__attribute__((used)) static int pctv452e_read_mac_address(struct dvb_usb_device *d, u8 mac[6])
{
	const u8 mem_addr[] = { 0x1f, 0xcc };
	u8 encoded_mac[20];
	int ret;

	ret = -EAGAIN;
	if (mutex_lock_interruptible(&d->i2c_mutex) < 0)
		goto failed;

	ret = pctv452e_i2c_msg(d, I2C_ADDR_24C16,
				mem_addr + 1, /* snd_len */ 1,
				encoded_mac, /* rcv_len */ 20);
	if (-EREMOTEIO == ret)
		/* Caution! A 24C16 interprets 0xA2 0x1F 0xCC as a
		   byte write if /WC is low. */
		ret = pctv452e_i2c_msg(d, I2C_ADDR_24C64,
					mem_addr, 2,
					encoded_mac, 20);

	mutex_unlock(&d->i2c_mutex);

	if (20 != ret)
		goto failed;

	ret = ttpci_eeprom_decode_mac(mac, encoded_mac);
	if (0 != ret)
		goto failed;

	return 0;

failed:
	eth_zero_addr(mac);

	return ret;
}