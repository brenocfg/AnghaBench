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
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/  nr; } ;
struct TYPE_3__ {int wren; int most; int clk; int data; } ;
struct bttv {int has_radio; int has_tea575x; int /*<<< orphan*/  tuner_type; TYPE_2__ c; void* tda9887_conf; TYPE_1__ tea_gpio; } ;

/* Variables and functions */
 scalar_t__ BTTV_BOARD_MIRO ; 
 scalar_t__ BTTV_BOARD_MIROPRO ; 
 scalar_t__ BTTV_BOARD_PINNACLE ; 
 void* BTTV_BOARD_PINNACLEPRO ; 
 int /*<<< orphan*/  I2C_ADDR_MSP3400 ; 
 void* TDA9887_INTERCARRIER ; 
 void* TDA9887_QSS ; 
 int /*<<< orphan*/  TUNER_MT2032 ; 
 int bttv_I2CRead (struct bttv*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_inout (int,int /*<<< orphan*/ ) ; 
 int gpio_read () ; 
 int /*<<< orphan*/ * miro_fmtuner ; 
 int /*<<< orphan*/ * miro_tunermap ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int,char*,char*,...) ; 
 int /*<<< orphan*/  tea575x_init (struct bttv*) ; 

__attribute__((used)) static void miro_pinnacle_gpio(struct bttv *btv)
{
	int id,msp,gpio;
	char *info;

	gpio_inout(0xffffff, 0);
	gpio = gpio_read();
	id   = ((gpio>>10) & 63) -1;
	msp  = bttv_I2CRead(btv, I2C_ADDR_MSP3400, "MSP34xx");
	if (id < 32) {
		btv->tuner_type = miro_tunermap[id];
		if (0 == (gpio & 0x20)) {
			btv->has_radio = 1;
			if (!miro_fmtuner[id]) {
				btv->has_tea575x = 1;
				btv->tea_gpio.wren = 6;
				btv->tea_gpio.most = 7;
				btv->tea_gpio.clk  = 8;
				btv->tea_gpio.data = 9;
				tea575x_init(btv);
			}
		} else {
			btv->has_radio = 0;
		}
		if (-1 != msp) {
			if (btv->c.type == BTTV_BOARD_MIRO)
				btv->c.type = BTTV_BOARD_MIROPRO;
			if (btv->c.type == BTTV_BOARD_PINNACLE)
				btv->c.type = BTTV_BOARD_PINNACLEPRO;
		}
		pr_info("%d: miro: id=%d tuner=%d radio=%s stereo=%s\n",
			btv->c.nr, id+1, btv->tuner_type,
			!btv->has_radio ? "no" :
			(btv->has_tea575x ? "tea575x" : "fmtuner"),
			(-1 == msp) ? "no" : "yes");
	} else {
		/* new cards with microtune tuner */
		id = 63 - id;
		btv->has_radio = 0;
		switch (id) {
		case 1:
			info = "PAL / mono";
			btv->tda9887_conf = TDA9887_INTERCARRIER;
			break;
		case 2:
			info = "PAL+SECAM / stereo";
			btv->has_radio = 1;
			btv->tda9887_conf = TDA9887_QSS;
			break;
		case 3:
			info = "NTSC / stereo";
			btv->has_radio = 1;
			btv->tda9887_conf = TDA9887_QSS;
			break;
		case 4:
			info = "PAL+SECAM / mono";
			btv->tda9887_conf = TDA9887_QSS;
			break;
		case 5:
			info = "NTSC / mono";
			btv->tda9887_conf = TDA9887_INTERCARRIER;
			break;
		case 6:
			info = "NTSC / stereo";
			btv->tda9887_conf = TDA9887_INTERCARRIER;
			break;
		case 7:
			info = "PAL / stereo";
			btv->tda9887_conf = TDA9887_INTERCARRIER;
			break;
		default:
			info = "oops: unknown card";
			break;
		}
		if (-1 != msp)
			btv->c.type = BTTV_BOARD_PINNACLEPRO;
		pr_info("%d: pinnacle/mt: id=%d info=\"%s\" radio=%s\n",
			btv->c.nr, id, info, btv->has_radio ? "yes" : "no");
		btv->tuner_type = TUNER_MT2032;
	}
}