#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_priv_tun_config {scalar_t__ type; int addr; scalar_t__* priv; int /*<<< orphan*/  tuner; int /*<<< orphan*/  mode_mask; } ;
struct tuner_setup {scalar_t__ type; int addr; scalar_t__* priv; int /*<<< orphan*/  tuner; int /*<<< orphan*/  mode_mask; } ;
struct TYPE_3__ {size_t type; int /*<<< orphan*/  i2c_adap; int /*<<< orphan*/  v4l2_dev; } ;
struct bttv {scalar_t__ tuner_type; scalar_t__ tda9887_conf; scalar_t__ has_radio; TYPE_1__ c; } ;
struct TYPE_4__ {int tuner_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRS_DEMOD ; 
 int /*<<< orphan*/  ADDRS_RADIO ; 
 int /*<<< orphan*/  ADDRS_TV_WITH_DEMOD ; 
 int ADDR_UNSET ; 
 scalar_t__ TUNER_ABSENT ; 
 int /*<<< orphan*/  TUNER_TDA9887 ; 
 int /*<<< orphan*/  T_ANALOG_TV ; 
 int /*<<< orphan*/  T_RADIO ; 
 int /*<<< orphan*/  bttv_call_all (struct bttv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_priv_tun_config*) ; 
 TYPE_2__* bttv_tvcards ; 
 int /*<<< orphan*/  s_config ; 
 int /*<<< orphan*/  s_type_addr ; 
 int /*<<< orphan*/  tuner ; 
 int /*<<< orphan*/  v4l2_i2c_new_subdev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_tuner_addrs (int /*<<< orphan*/ ) ; 

void bttv_init_tuner(struct bttv *btv)
{
	int addr = ADDR_UNSET;

	if (ADDR_UNSET != bttv_tvcards[btv->c.type].tuner_addr)
		addr = bttv_tvcards[btv->c.type].tuner_addr;

	if (btv->tuner_type != TUNER_ABSENT) {
		struct tuner_setup tun_setup;

		/* Load tuner module before issuing tuner config call! */
		if (btv->has_radio)
			v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
				&btv->c.i2c_adap, "tuner",
				0, v4l2_i2c_tuner_addrs(ADDRS_RADIO));
		v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
				&btv->c.i2c_adap, "tuner",
				0, v4l2_i2c_tuner_addrs(ADDRS_DEMOD));
		v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
				&btv->c.i2c_adap, "tuner",
				0, v4l2_i2c_tuner_addrs(ADDRS_TV_WITH_DEMOD));

		tun_setup.mode_mask = T_ANALOG_TV;
		tun_setup.type = btv->tuner_type;
		tun_setup.addr = addr;

		if (btv->has_radio)
			tun_setup.mode_mask |= T_RADIO;

		bttv_call_all(btv, tuner, s_type_addr, &tun_setup);
	}

	if (btv->tda9887_conf) {
		struct v4l2_priv_tun_config tda9887_cfg;

		tda9887_cfg.tuner = TUNER_TDA9887;
		tda9887_cfg.priv = &btv->tda9887_conf;

		bttv_call_all(btv, tuner, s_config, &tda9887_cfg);
	}
}