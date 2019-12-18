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
struct i2c_client {int dummy; } ;
struct i2c_board_info {char* name; int addr; struct i2c_board_info* platform_data; int /*<<< orphan*/  ir_codes; int /*<<< orphan*/  get_key; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int type; int /*<<< orphan*/  i2c_adap; } ;
struct bttv {scalar_t__ i2c_rc; TYPE_1__ c; struct i2c_board_info init_data; } ;

/* Variables and functions */
#define  BTTV_BOARD_PV951 129 
#define  I2C_CLIENT_END 128 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  RC_MAP_PV951 ; 
 int /*<<< orphan*/  get_key_pv951 ; 
 struct i2c_client* i2c_new_device (int /*<<< orphan*/ *,struct i2c_board_info*) ; 
 struct i2c_client* i2c_new_probed_device (int /*<<< orphan*/ *,struct i2c_board_info*,unsigned short const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct i2c_board_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  request_module (char*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void init_bttv_i2c_ir(struct bttv *btv)
{
	static const unsigned short addr_list[] = {
		0x1a, 0x18, 0x64, 0x30, 0x71,
		I2C_CLIENT_END
	};
	struct i2c_board_info info;
	struct i2c_client *i2c_dev;

	if (0 != btv->i2c_rc)
		return;

	memset(&info, 0, sizeof(struct i2c_board_info));
	memset(&btv->init_data, 0, sizeof(btv->init_data));
	strscpy(info.type, "ir_video", I2C_NAME_SIZE);

	switch (btv->c.type) {
	case BTTV_BOARD_PV951:
		btv->init_data.name = "PV951";
		btv->init_data.get_key = get_key_pv951;
		btv->init_data.ir_codes = RC_MAP_PV951;
		info.addr = 0x4b;
		break;
	}

	if (btv->init_data.name) {
		info.platform_data = &btv->init_data;
		i2c_dev = i2c_new_device(&btv->c.i2c_adap, &info);
	} else {
		/*
		 * The external IR receiver is at i2c address 0x34 (0x35 for
		 * reads).  Future Hauppauge cards will have an internal
		 * receiver at 0x30 (0x31 for reads).  In theory, both can be
		 * fitted, and Hauppauge suggest an external overrides an
		 * internal.
		 * That's why we probe 0x1a (~0x34) first. CB
		 */
		i2c_dev = i2c_new_probed_device(&btv->c.i2c_adap, &info, addr_list, NULL);
	}
	if (NULL == i2c_dev)
		return;

#if defined(CONFIG_MODULES) && defined(MODULE)
	request_module("ir-kbd-i2c");
#endif
}