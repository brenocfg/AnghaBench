#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct TYPE_7__ {int type; size_t nr; int /*<<< orphan*/  i2c_adap; int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_6__ {int pll_ifreq; int pll_current; void* pll_crystal; int /*<<< orphan*/  pll_ofreq; } ;
struct TYPE_5__ {int wren; int most; int clk; int data; } ;
struct bttv {scalar_t__ tuner_type; int has_radio; int has_tea575x; int cardid; int id; int revision; int has_remote; int gpioirq; TYPE_3__ c; void* sd_tvaudio; void* sd_tda7432; void* sd_msp34xx; scalar_t__ has_saa6588; scalar_t__ audio_mode_gpio; scalar_t__ volume_gpio; scalar_t__ svhs; scalar_t__ dig; TYPE_2__ pll; TYPE_1__ tea_gpio; } ;
struct TYPE_8__ {scalar_t__ pll; scalar_t__ tuner_type; scalar_t__ video_inputs; scalar_t__ svhs; int /*<<< orphan*/  no_tda7432; scalar_t__ msp34xx_alt; int /*<<< orphan*/  no_msp34xx; scalar_t__ audio_mode_gpio; scalar_t__ volume_gpio; int /*<<< orphan*/  no_gpioirq; scalar_t__ has_remote; scalar_t__ has_radio; scalar_t__ has_dig_in; } ;

/* Variables and functions */
 void* BT848_IFORM_XT0 ; 
 void* BT848_IFORM_XT1 ; 
#define  BTTV_BOARD_AVERMEDIA98 176 
#define  BTTV_BOARD_AVPHONE98 175 
#define  BTTV_BOARD_CHRONOS_VS2 174 
#define  BTTV_BOARD_CONFERENCETV 173 
#define  BTTV_BOARD_FLYVIDEO 172 
#define  BTTV_BOARD_FLYVIDEO2000 171 
#define  BTTV_BOARD_FLYVIDEO98EZ 170 
#define  BTTV_BOARD_FLYVIDEO_98 169 
#define  BTTV_BOARD_FLYVIDEO_98FM 168 
#define  BTTV_BOARD_GEOVISION_GV800S 167 
#define  BTTV_BOARD_HAUPPAUGE 166 
#define  BTTV_BOARD_HAUPPAUGE878 165 
#define  BTTV_BOARD_HAUPPAUGEPVR 164 
#define  BTTV_BOARD_IDS_EAGLE 163 
#define  BTTV_BOARD_KODICOM_4400R 162 
#define  BTTV_BOARD_LIFETEC_9415 161 
#define  BTTV_BOARD_LIFE_FLYKIT 160 
#define  BTTV_BOARD_LMLBT4 159 
#define  BTTV_BOARD_MAGICTVIEW061 158 
#define  BTTV_BOARD_MAXI 157 
#define  BTTV_BOARD_MIRO 156 
#define  BTTV_BOARD_MIROPRO 155 
#define  BTTV_BOARD_MODTEC_205 154 
#define  BTTV_BOARD_OSPREY101_848 153 
#define  BTTV_BOARD_OSPREY1x0 152 
#define  BTTV_BOARD_OSPREY1x0_848 151 
#define  BTTV_BOARD_OSPREY1x1 150 
#define  BTTV_BOARD_OSPREY1x1_SVID 149 
#define  BTTV_BOARD_OSPREY2000 148 
#define  BTTV_BOARD_OSPREY2x0 147 
#define  BTTV_BOARD_OSPREY2x0_SVID 146 
#define  BTTV_BOARD_OSPREY2xx 145 
#define  BTTV_BOARD_OSPREY440 144 
#define  BTTV_BOARD_OSPREY500 143 
#define  BTTV_BOARD_OSPREY540 142 
#define  BTTV_BOARD_PICOLO_TETRA_CHIP 141 
#define  BTTV_BOARD_PINNACLE 140 
#define  BTTV_BOARD_PINNACLEPRO 139 
#define  BTTV_BOARD_PXC200 138 
#define  BTTV_BOARD_STB2 137 
#define  BTTV_BOARD_TERRATV 136 
#define  BTTV_BOARD_TIBET_CS16 135 
#define  BTTV_BOARD_TYPHOON_TVIEW 134 
 int BTTV_BOARD_UNKNOWN ; 
#define  BTTV_BOARD_VHX 133 
#define  BTTV_BOARD_VOBIS_BOOSTAR 132 
 unsigned short const* I2C_ADDRS (int const) ; 
#define  I2C_ADDR_MSP3400 131 
#define  I2C_ADDR_MSP3400_ALT 130 
#define  I2C_ADDR_TDA7432 129 
#define  I2C_CLIENT_END 128 
 scalar_t__ NO_SVHS ; 
 scalar_t__ PLL_14 ; 
 scalar_t__ PLL_28 ; 
 scalar_t__ PLL_35 ; 
 scalar_t__ TUNER_ABSENT ; 
 scalar_t__ TUNER_TEMIC_NTSC ; 
 scalar_t__ UNSET ; 
 int* audiodev ; 
 scalar_t__ autoload ; 
 int /*<<< orphan*/  avermedia_eeprom (struct bttv*) ; 
 int /*<<< orphan*/  bttv_readee (struct bttv*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* bttv_tvcards ; 
 int /*<<< orphan*/  eeprom_data ; 
 int /*<<< orphan*/  flyvideo_gpio (struct bttv*) ; 
 int /*<<< orphan*/  gv800s_init (struct bttv*) ; 
 int /*<<< orphan*/  hauppauge_eeprom (struct bttv*) ; 
 int /*<<< orphan*/  identify_by_eeprom (struct bttv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_PXC200 (struct bttv*) ; 
 int /*<<< orphan*/  init_ids_eagle (struct bttv*) ; 
 int /*<<< orphan*/  init_lmlbt4x (struct bttv*) ; 
 int /*<<< orphan*/  kodicom4400r_init (struct bttv*) ; 
 int /*<<< orphan*/  miro_pinnacle_gpio (struct bttv*) ; 
 int /*<<< orphan*/  modtec_eeprom (struct bttv*) ; 
 int /*<<< orphan*/  osprey_eeprom (struct bttv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  picolo_tetra_init (struct bttv*) ; 
 int* pll ; 
 int /*<<< orphan*/  pr_info (char*,size_t,...) ; 
 int /*<<< orphan*/  pr_warn (char*,size_t) ; 
 scalar_t__* remote ; 
 scalar_t__* saa6588 ; 
 scalar_t__* svhs ; 
 int /*<<< orphan*/  tea575x_init (struct bttv*) ; 
 int /*<<< orphan*/  terratec_active_radio_upgrade (struct bttv*) ; 
 int /*<<< orphan*/  tibetCS16_init (struct bttv*) ; 
 scalar_t__* tuner ; 
 unsigned short const* tvaudio_addrs () ; 
 void* v4l2_i2c_new_subdev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned short const*) ; 

void bttv_init_card2(struct bttv *btv)
{
	btv->tuner_type = UNSET;

	if (BTTV_BOARD_UNKNOWN == btv->c.type) {
		bttv_readee(btv,eeprom_data,0xa0);
		identify_by_eeprom(btv,eeprom_data);
	}

	switch (btv->c.type) {
	case BTTV_BOARD_MIRO:
	case BTTV_BOARD_MIROPRO:
	case BTTV_BOARD_PINNACLE:
	case BTTV_BOARD_PINNACLEPRO:
		/* miro/pinnacle */
		miro_pinnacle_gpio(btv);
		break;
	case BTTV_BOARD_FLYVIDEO_98:
	case BTTV_BOARD_MAXI:
	case BTTV_BOARD_LIFE_FLYKIT:
	case BTTV_BOARD_FLYVIDEO:
	case BTTV_BOARD_TYPHOON_TVIEW:
	case BTTV_BOARD_CHRONOS_VS2:
	case BTTV_BOARD_FLYVIDEO_98FM:
	case BTTV_BOARD_FLYVIDEO2000:
	case BTTV_BOARD_FLYVIDEO98EZ:
	case BTTV_BOARD_CONFERENCETV:
	case BTTV_BOARD_LIFETEC_9415:
		flyvideo_gpio(btv);
		break;
	case BTTV_BOARD_HAUPPAUGE:
	case BTTV_BOARD_HAUPPAUGE878:
	case BTTV_BOARD_HAUPPAUGEPVR:
		/* pick up some config infos from the eeprom */
		bttv_readee(btv,eeprom_data,0xa0);
		hauppauge_eeprom(btv);
		break;
	case BTTV_BOARD_AVERMEDIA98:
	case BTTV_BOARD_AVPHONE98:
		bttv_readee(btv,eeprom_data,0xa0);
		avermedia_eeprom(btv);
		break;
	case BTTV_BOARD_PXC200:
		init_PXC200(btv);
		break;
	case BTTV_BOARD_PICOLO_TETRA_CHIP:
		picolo_tetra_init(btv);
		break;
	case BTTV_BOARD_VHX:
		btv->has_radio    = 1;
		btv->has_tea575x  = 1;
		btv->tea_gpio.wren = 5;
		btv->tea_gpio.most = 6;
		btv->tea_gpio.clk  = 3;
		btv->tea_gpio.data = 4;
		tea575x_init(btv);
		break;
	case BTTV_BOARD_VOBIS_BOOSTAR:
	case BTTV_BOARD_TERRATV:
		terratec_active_radio_upgrade(btv);
		break;
	case BTTV_BOARD_MAGICTVIEW061:
		if (btv->cardid == 0x3002144f) {
			btv->has_radio=1;
			pr_info("%d: radio detected by subsystem id (CPH05x)\n",
				btv->c.nr);
		}
		break;
	case BTTV_BOARD_STB2:
		if (btv->cardid == 0x3060121a) {
			/* Fix up entry for 3DFX VoodooTV 100,
			   which is an OEM STB card variant. */
			btv->has_radio=0;
			btv->tuner_type=TUNER_TEMIC_NTSC;
		}
		break;
	case BTTV_BOARD_OSPREY1x0:
	case BTTV_BOARD_OSPREY1x0_848:
	case BTTV_BOARD_OSPREY101_848:
	case BTTV_BOARD_OSPREY1x1:
	case BTTV_BOARD_OSPREY1x1_SVID:
	case BTTV_BOARD_OSPREY2xx:
	case BTTV_BOARD_OSPREY2x0_SVID:
	case BTTV_BOARD_OSPREY2x0:
	case BTTV_BOARD_OSPREY440:
	case BTTV_BOARD_OSPREY500:
	case BTTV_BOARD_OSPREY540:
	case BTTV_BOARD_OSPREY2000:
		bttv_readee(btv,eeprom_data,0xa0);
		osprey_eeprom(btv, eeprom_data);
		break;
	case BTTV_BOARD_IDS_EAGLE:
		init_ids_eagle(btv);
		break;
	case BTTV_BOARD_MODTEC_205:
		bttv_readee(btv,eeprom_data,0xa0);
		modtec_eeprom(btv);
		break;
	case BTTV_BOARD_LMLBT4:
		init_lmlbt4x(btv);
		break;
	case BTTV_BOARD_TIBET_CS16:
		tibetCS16_init(btv);
		break;
	case BTTV_BOARD_KODICOM_4400R:
		kodicom4400r_init(btv);
		break;
	case BTTV_BOARD_GEOVISION_GV800S:
		gv800s_init(btv);
		break;
	}

	/* pll configuration */
	if (!(btv->id==848 && btv->revision==0x11)) {
		/* defaults from card list */
		if (PLL_28 == bttv_tvcards[btv->c.type].pll) {
			btv->pll.pll_ifreq=28636363;
			btv->pll.pll_crystal=BT848_IFORM_XT0;
		}
		if (PLL_35 == bttv_tvcards[btv->c.type].pll) {
			btv->pll.pll_ifreq=35468950;
			btv->pll.pll_crystal=BT848_IFORM_XT1;
		}
		if (PLL_14 == bttv_tvcards[btv->c.type].pll) {
			btv->pll.pll_ifreq = 14318181;
			btv->pll.pll_crystal = BT848_IFORM_XT0;
		}
		/* insmod options can override */
		switch (pll[btv->c.nr]) {
		case 0: /* none */
			btv->pll.pll_crystal = 0;
			btv->pll.pll_ifreq   = 0;
			btv->pll.pll_ofreq   = 0;
			break;
		case 1: /* 28 MHz */
		case 28:
			btv->pll.pll_ifreq   = 28636363;
			btv->pll.pll_ofreq   = 0;
			btv->pll.pll_crystal = BT848_IFORM_XT0;
			break;
		case 2: /* 35 MHz */
		case 35:
			btv->pll.pll_ifreq   = 35468950;
			btv->pll.pll_ofreq   = 0;
			btv->pll.pll_crystal = BT848_IFORM_XT1;
			break;
		case 3: /* 14 MHz */
		case 14:
			btv->pll.pll_ifreq   = 14318181;
			btv->pll.pll_ofreq   = 0;
			btv->pll.pll_crystal = BT848_IFORM_XT0;
			break;
		}
	}
	btv->pll.pll_current = -1;

	/* tuner configuration (from card list / autodetect / insmod option) */
	if (UNSET != bttv_tvcards[btv->c.type].tuner_type)
		if (UNSET == btv->tuner_type)
			btv->tuner_type = bttv_tvcards[btv->c.type].tuner_type;
	if (UNSET != tuner[btv->c.nr])
		btv->tuner_type = tuner[btv->c.nr];

	if (btv->tuner_type == TUNER_ABSENT)
		pr_info("%d: tuner absent\n", btv->c.nr);
	else if (btv->tuner_type == UNSET)
		pr_warn("%d: tuner type unset\n", btv->c.nr);
	else
		pr_info("%d: tuner type=%d\n", btv->c.nr, btv->tuner_type);

	if (autoload != UNSET) {
		pr_warn("%d: the autoload option is obsolete\n", btv->c.nr);
		pr_warn("%d: use option msp3400, tda7432 or tvaudio to override which audio module should be used\n",
			btv->c.nr);
	}

	if (UNSET == btv->tuner_type)
		btv->tuner_type = TUNER_ABSENT;

	btv->dig = bttv_tvcards[btv->c.type].has_dig_in ?
		   bttv_tvcards[btv->c.type].video_inputs - 1 : UNSET;
	btv->svhs = bttv_tvcards[btv->c.type].svhs == NO_SVHS ?
		    UNSET : bttv_tvcards[btv->c.type].svhs;
	if (svhs[btv->c.nr] != UNSET)
		btv->svhs = svhs[btv->c.nr];
	if (remote[btv->c.nr] != UNSET)
		btv->has_remote = remote[btv->c.nr];

	if (bttv_tvcards[btv->c.type].has_radio)
		btv->has_radio = 1;
	if (bttv_tvcards[btv->c.type].has_remote)
		btv->has_remote = 1;
	if (!bttv_tvcards[btv->c.type].no_gpioirq)
		btv->gpioirq = 1;
	if (bttv_tvcards[btv->c.type].volume_gpio)
		btv->volume_gpio = bttv_tvcards[btv->c.type].volume_gpio;
	if (bttv_tvcards[btv->c.type].audio_mode_gpio)
		btv->audio_mode_gpio = bttv_tvcards[btv->c.type].audio_mode_gpio;

	if (btv->tuner_type == TUNER_ABSENT)
		return;  /* no tuner or related drivers to load */

	if (btv->has_saa6588 || saa6588[btv->c.nr]) {
		/* Probe for RDS receiver chip */
		static const unsigned short addrs[] = {
			0x20 >> 1,
			0x22 >> 1,
			I2C_CLIENT_END
		};
		struct v4l2_subdev *sd;

		sd = v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
			&btv->c.i2c_adap, "saa6588", 0, addrs);
		btv->has_saa6588 = (sd != NULL);
	}

	/* try to detect audio/fader chips */

	/* First check if the user specified the audio chip via a module
	   option. */

	switch (audiodev[btv->c.nr]) {
	case -1:
		return;	/* do not load any audio module */

	case 0: /* autodetect */
		break;

	case 1: {
		/* The user specified that we should probe for msp3400 */
		static const unsigned short addrs[] = {
			I2C_ADDR_MSP3400 >> 1,
			I2C_ADDR_MSP3400_ALT >> 1,
			I2C_CLIENT_END
		};

		btv->sd_msp34xx = v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
			&btv->c.i2c_adap, "msp3400", 0, addrs);
		if (btv->sd_msp34xx)
			return;
		goto no_audio;
	}

	case 2: {
		/* The user specified that we should probe for tda7432 */
		static const unsigned short addrs[] = {
			I2C_ADDR_TDA7432 >> 1,
			I2C_CLIENT_END
		};

		if (v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
				&btv->c.i2c_adap, "tda7432", 0, addrs))
			return;
		goto no_audio;
	}

	case 3: {
		/* The user specified that we should probe for tvaudio */
		btv->sd_tvaudio = v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
			&btv->c.i2c_adap, "tvaudio", 0, tvaudio_addrs());
		if (btv->sd_tvaudio)
			return;
		goto no_audio;
	}

	default:
		pr_warn("%d: unknown audiodev value!\n", btv->c.nr);
		return;
	}

	/* There were no overrides, so now we try to discover this through the
	   card definition */

	/* probe for msp3400 first: this driver can detect whether or not
	   it really is a msp3400, so it will return NULL when the device
	   found is really something else (e.g. a tea6300). */
	if (!bttv_tvcards[btv->c.type].no_msp34xx) {
		btv->sd_msp34xx = v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
			&btv->c.i2c_adap, "msp3400",
			0, I2C_ADDRS(I2C_ADDR_MSP3400 >> 1));
	} else if (bttv_tvcards[btv->c.type].msp34xx_alt) {
		btv->sd_msp34xx = v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
			&btv->c.i2c_adap, "msp3400",
			0, I2C_ADDRS(I2C_ADDR_MSP3400_ALT >> 1));
	}

	/* If we found a msp34xx, then we're done. */
	if (btv->sd_msp34xx)
		return;

	/* Now see if we can find one of the tvaudio devices. */
	btv->sd_tvaudio = v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
		&btv->c.i2c_adap, "tvaudio", 0, tvaudio_addrs());
	if (btv->sd_tvaudio) {
		/* There may be two tvaudio chips on the card, so try to
		   find another. */
		v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
			&btv->c.i2c_adap, "tvaudio", 0, tvaudio_addrs());
	}

	/* it might also be a tda7432. */
	if (!bttv_tvcards[btv->c.type].no_tda7432) {
		static const unsigned short addrs[] = {
			I2C_ADDR_TDA7432 >> 1,
			I2C_CLIENT_END
		};

		btv->sd_tda7432 = v4l2_i2c_new_subdev(&btv->c.v4l2_dev,
				&btv->c.i2c_adap, "tda7432", 0, addrs);
		if (btv->sd_tda7432)
			return;
	}
	if (btv->sd_tvaudio)
		return;

no_audio:
	pr_warn("%d: audio absent, no audio device found!\n", btv->c.nr);
}