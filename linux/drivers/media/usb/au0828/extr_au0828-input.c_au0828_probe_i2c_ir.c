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
struct TYPE_2__ {int /*<<< orphan*/  adapter; } ;
struct au0828_dev {TYPE_1__ i2c_client; } ;

/* Variables and functions */
 int ENODEV ; 
#define  I2C_CLIENT_END 128 
 int i2c_probe_func_quick_read (int /*<<< orphan*/ ,unsigned short const) ; 

__attribute__((used)) static int au0828_probe_i2c_ir(struct au0828_dev *dev)
{
	int i = 0;
	static const unsigned short addr_list[] = {
		 0x47, I2C_CLIENT_END
	};

	while (addr_list[i] != I2C_CLIENT_END) {
		if (i2c_probe_func_quick_read(dev->i2c_client.adapter,
					      addr_list[i]) == 1)
			return addr_list[i];
		i++;
	}

	return -ENODEV;
}