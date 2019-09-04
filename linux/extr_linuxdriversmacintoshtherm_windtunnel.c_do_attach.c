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
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int running; int /*<<< orphan*/  poll_task; scalar_t__ fan; scalar_t__ thermostat; } ;

/* Variables and functions */
#define  I2C_CLIENT_END 128 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  control_loop ; 
 int /*<<< orphan*/  i2c_new_probed_device (struct i2c_adapter*,struct i2c_board_info*,unsigned short const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (struct i2c_board_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__ x ; 

__attribute__((used)) static int
do_attach( struct i2c_adapter *adapter )
{
	/* scan 0x48-0x4f (DS1775) and 0x2c-2x2f (ADM1030) */
	static const unsigned short scan_ds1775[] = {
		0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
		I2C_CLIENT_END
	};
	static const unsigned short scan_adm1030[] = {
		0x2c, 0x2d, 0x2e, 0x2f,
		I2C_CLIENT_END
	};

	if( strncmp(adapter->name, "uni-n", 5) )
		return 0;

	if( !x.running ) {
		struct i2c_board_info info;

		memset(&info, 0, sizeof(struct i2c_board_info));
		strlcpy(info.type, "therm_ds1775", I2C_NAME_SIZE);
		i2c_new_probed_device(adapter, &info, scan_ds1775, NULL);

		strlcpy(info.type, "therm_adm1030", I2C_NAME_SIZE);
		i2c_new_probed_device(adapter, &info, scan_adm1030, NULL);

		if( x.thermostat && x.fan ) {
			x.running = 1;
			x.poll_task = kthread_run(control_loop, NULL, "g4fand");
		}
	}
	return 0;
}