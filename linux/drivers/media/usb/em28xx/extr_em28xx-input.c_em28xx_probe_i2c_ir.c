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
struct em28xx {size_t def_i2c_bus; int /*<<< orphan*/ * i2c_adap; } ;

/* Variables and functions */
 int ENODEV ; 
#define  I2C_CLIENT_END 128 
 int i2c_probe_func_quick_read (int /*<<< orphan*/ *,unsigned short const) ; 

__attribute__((used)) static int em28xx_probe_i2c_ir(struct em28xx *dev)
{
	int i = 0;
	/*
	 * Leadtek winfast tv USBII deluxe can find a non working IR-device
	 * at address 0x18, so if that address is needed for another board in
	 * the future, please put it after 0x1f.
	 */
	static const unsigned short addr_list[] = {
		 0x1f, 0x30, 0x47, I2C_CLIENT_END
	};

	while (addr_list[i] != I2C_CLIENT_END) {
		if (i2c_probe_func_quick_read(&dev->i2c_adap[dev->def_i2c_bus],
					      addr_list[i]) == 1)
			return addr_list[i];
		i++;
	}

	return -ENODEV;
}