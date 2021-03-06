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
struct saa7134_dev {int board; void* has_remote; int /*<<< orphan*/  name; int /*<<< orphan*/  gpio_value; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  SAA7134_BOARD_10MOONSTVMASTER3 248 
#define  SAA7134_BOARD_ADS_DUO_CARDBUS_PTV331 247 
#define  SAA7134_BOARD_ASUSTeK_P7131_ANALOG 246 
#define  SAA7134_BOARD_ASUSTeK_P7131_DUAL 245 
#define  SAA7134_BOARD_ASUSTeK_P7131_HYBRID_LNA 244 
#define  SAA7134_BOARD_ASUSTeK_PS3_100 243 
#define  SAA7134_BOARD_AVACSSMARTTV 242 
#define  SAA7134_BOARD_AVERMEDIA_305 241 
#define  SAA7134_BOARD_AVERMEDIA_307 240 
#define  SAA7134_BOARD_AVERMEDIA_505 239 
#define  SAA7134_BOARD_AVERMEDIA_777 238 
#define  SAA7134_BOARD_AVERMEDIA_A169_B 237 
#define  SAA7134_BOARD_AVERMEDIA_A16AR 236 
#define  SAA7134_BOARD_AVERMEDIA_A16D 235 
#define  SAA7134_BOARD_AVERMEDIA_A700_HYBRID 234 
#define  SAA7134_BOARD_AVERMEDIA_A700_PRO 233 
#define  SAA7134_BOARD_AVERMEDIA_A706 232 
#define  SAA7134_BOARD_AVERMEDIA_CARDBUS 231 
#define  SAA7134_BOARD_AVERMEDIA_CARDBUS_501 230 
#define  SAA7134_BOARD_AVERMEDIA_CARDBUS_506 229 
#define  SAA7134_BOARD_AVERMEDIA_GO_007_FM 228 
#define  SAA7134_BOARD_AVERMEDIA_GO_007_FM_PLUS 227 
#define  SAA7134_BOARD_AVERMEDIA_M102 226 
#define  SAA7134_BOARD_AVERMEDIA_M103 225 
#define  SAA7134_BOARD_AVERMEDIA_M115 224 
#define  SAA7134_BOARD_AVERMEDIA_M135A 223 
#define  SAA7134_BOARD_AVERMEDIA_M733A 222 
#define  SAA7134_BOARD_AVERMEDIA_STUDIO_305 221 
#define  SAA7134_BOARD_AVERMEDIA_STUDIO_307 220 
#define  SAA7134_BOARD_AVERMEDIA_STUDIO_505 219 
#define  SAA7134_BOARD_AVERMEDIA_STUDIO_507 218 
#define  SAA7134_BOARD_BEHOLD_401 217 
#define  SAA7134_BOARD_BEHOLD_403 216 
#define  SAA7134_BOARD_BEHOLD_403FM 215 
#define  SAA7134_BOARD_BEHOLD_405 214 
#define  SAA7134_BOARD_BEHOLD_405FM 213 
#define  SAA7134_BOARD_BEHOLD_407 212 
#define  SAA7134_BOARD_BEHOLD_407FM 211 
#define  SAA7134_BOARD_BEHOLD_409 210 
#define  SAA7134_BOARD_BEHOLD_409FM 209 
#define  SAA7134_BOARD_BEHOLD_505FM 208 
#define  SAA7134_BOARD_BEHOLD_505RDS_MK3 207 
#define  SAA7134_BOARD_BEHOLD_505RDS_MK5 206 
#define  SAA7134_BOARD_BEHOLD_507RDS_MK3 205 
#define  SAA7134_BOARD_BEHOLD_507RDS_MK5 204 
#define  SAA7134_BOARD_BEHOLD_507_9FM 203 
#define  SAA7134_BOARD_BEHOLD_607FM_MK3 202 
#define  SAA7134_BOARD_BEHOLD_607FM_MK5 201 
#define  SAA7134_BOARD_BEHOLD_607RDS_MK3 200 
#define  SAA7134_BOARD_BEHOLD_607RDS_MK5 199 
#define  SAA7134_BOARD_BEHOLD_609FM_MK3 198 
#define  SAA7134_BOARD_BEHOLD_609FM_MK5 197 
#define  SAA7134_BOARD_BEHOLD_609RDS_MK3 196 
#define  SAA7134_BOARD_BEHOLD_609RDS_MK5 195 
#define  SAA7134_BOARD_BEHOLD_A7 194 
#define  SAA7134_BOARD_BEHOLD_COLUMBUS_TVFM 193 
#define  SAA7134_BOARD_BEHOLD_H6 192 
#define  SAA7134_BOARD_BEHOLD_H7 191 
#define  SAA7134_BOARD_BEHOLD_M6 190 
#define  SAA7134_BOARD_BEHOLD_M63 189 
#define  SAA7134_BOARD_BEHOLD_M6_EXTRA 188 
#define  SAA7134_BOARD_BEHOLD_X7 187 
#define  SAA7134_BOARD_CINERGY400 186 
#define  SAA7134_BOARD_CINERGY400_CARDBUS 185 
#define  SAA7134_BOARD_CINERGY600 184 
#define  SAA7134_BOARD_CINERGY600_MK3 183 
#define  SAA7134_BOARD_ECS_TVP3XP 182 
#define  SAA7134_BOARD_ECS_TVP3XP_4CB5 181 
#define  SAA7134_BOARD_ECS_TVP3XP_4CB6 180 
#define  SAA7134_BOARD_ENCORE_ENLTV 179 
#define  SAA7134_BOARD_ENCORE_ENLTV_FM 178 
#define  SAA7134_BOARD_ENCORE_ENLTV_FM3 177 
#define  SAA7134_BOARD_ENCORE_ENLTV_FM53 176 
#define  SAA7134_BOARD_FLYDVBS_LR300 175 
#define  SAA7134_BOARD_FLYDVBTDUO 174 
#define  SAA7134_BOARD_FLYDVBT_DUO_CARDBUS 173 
#define  SAA7134_BOARD_FLYDVBT_HYBRID_CARDBUS 172 
#define  SAA7134_BOARD_FLYDVBT_LR301 171 
#define  SAA7134_BOARD_FLYTVPLATINUM_FM 170 
#define  SAA7134_BOARD_FLYTVPLATINUM_MINI2 169 
#define  SAA7134_BOARD_FLYVIDEO2000 168 
#define  SAA7134_BOARD_FLYVIDEO3000 167 
#define  SAA7134_BOARD_FLYVIDEO3000_NTSC 166 
#define  SAA7134_BOARD_GENIUS_TVGO_A11MCE 165 
#define  SAA7134_BOARD_GOTVIEW_7135 164 
#define  SAA7134_BOARD_HAUPPAUGE_HVR1110 163 
#define  SAA7134_BOARD_HAUPPAUGE_HVR1120 162 
#define  SAA7134_BOARD_HAUPPAUGE_HVR1150 161 
#define  SAA7134_BOARD_KWORLD_PC150U 160 
#define  SAA7134_BOARD_KWORLD_PLUS_TV_ANALOG 159 
#define  SAA7134_BOARD_KWORLD_TERMINATOR 158 
#define  SAA7134_BOARD_KWORLD_VSTREAM_XPERT 157 
#define  SAA7134_BOARD_KWORLD_XPERT 156 
#define  SAA7134_BOARD_LEADTEK_WINFAST_DTV1000S 155 
#define  SAA7134_BOARD_LEADTEK_WINFAST_TV2100_FM 154 
#define  SAA7134_BOARD_MAGICPRO_PROHDTV_PRO2 153 
#define  SAA7134_BOARD_MANLI_MTV001 152 
#define  SAA7134_BOARD_MANLI_MTV002 151 
#define  SAA7134_BOARD_MD2819 150 
#define  SAA7134_BOARD_MD5044 149 
#define  SAA7134_BOARD_MONSTERTV_MOBILE 148 
#define  SAA7134_BOARD_MSI_TVATANYWHERE_PLUS 147 
#define  SAA7134_BOARD_PINNACLE_300I_DVBT_PAL 146 
#define  SAA7134_BOARD_PINNACLE_PCTV_110i 145 
#define  SAA7134_BOARD_PINNACLE_PCTV_310i 144 
#define  SAA7134_BOARD_PROTEUS_2309 143 
#define  SAA7134_BOARD_REAL_ANGEL_220 142 
#define  SAA7134_BOARD_ROVERMEDIA_LINK_PRO_FM 141 
#define  SAA7134_BOARD_RTD_VFG7350 140 
#define  SAA7134_BOARD_SEDNA_PC_TV_CARDBUS 139 
#define  SAA7134_BOARD_SNAZIO_TVPVR_PRO 138 
#define  SAA7134_BOARD_UPMOST_PURPLE_TV 137 
#define  SAA7134_BOARD_VIDEOMATE_DVBT_200 136 
#define  SAA7134_BOARD_VIDEOMATE_DVBT_200A 135 
#define  SAA7134_BOARD_VIDEOMATE_DVBT_300 134 
#define  SAA7134_BOARD_VIDEOMATE_GOLD_PLUS 133 
#define  SAA7134_BOARD_VIDEOMATE_M1F 132 
#define  SAA7134_BOARD_VIDEOMATE_S350 131 
#define  SAA7134_BOARD_VIDEOMATE_T750 130 
#define  SAA7134_BOARD_VIDEOMATE_TV_GOLD_PLUSII 129 
#define  SAA7134_BOARD_VIDEOMATE_TV_PVR 128 
 int SAA7134_GPIO_GPMODE0 ; 
 int /*<<< orphan*/  SAA7134_GPIO_GPMODE1 ; 
 int /*<<< orphan*/  SAA7134_GPIO_GPMODE3 ; 
 int SAA7134_GPIO_GPSTATUS0 ; 
 int /*<<< orphan*/  SAA7134_GPIO_GPSTATUS1 ; 
 int /*<<< orphan*/  SAA7134_GPIO_GPSTATUS2 ; 
 int /*<<< orphan*/  SAA7134_GPIO_GPSTATUS3 ; 
 int /*<<< orphan*/  SAA7134_PRODUCTION_TEST_MODE ; 
 void* SAA7134_REMOTE_GPIO ; 
 void* SAA7134_REMOTE_I2C ; 
 int /*<<< orphan*/  board_flyvideo (struct saa7134_dev*) ; 
 TYPE_1__ card (struct saa7134_dev*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  saa7134_set_gpio (struct saa7134_dev*,int,int) ; 
 int /*<<< orphan*/  saa_andorl (int,int,int) ; 
 int /*<<< orphan*/  saa_readl (int) ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  saa_writel (int,int /*<<< orphan*/ ) ; 

int saa7134_board_init1(struct saa7134_dev *dev)
{
	/* Always print gpio, often manufacturers encode tuner type and other info. */
	saa_writel(SAA7134_GPIO_GPMODE0 >> 2, 0);
	dev->gpio_value = saa_readl(SAA7134_GPIO_GPSTATUS0 >> 2);
	pr_info("%s: board init: gpio is %x\n", dev->name, dev->gpio_value);

	switch (dev->board) {
	case SAA7134_BOARD_FLYVIDEO2000:
	case SAA7134_BOARD_FLYVIDEO3000:
	case SAA7134_BOARD_FLYVIDEO3000_NTSC:
		dev->has_remote = SAA7134_REMOTE_GPIO;
		board_flyvideo(dev);
		break;
	case SAA7134_BOARD_FLYTVPLATINUM_MINI2:
	case SAA7134_BOARD_FLYTVPLATINUM_FM:
	case SAA7134_BOARD_CINERGY400:
	case SAA7134_BOARD_CINERGY600:
	case SAA7134_BOARD_CINERGY600_MK3:
	case SAA7134_BOARD_ECS_TVP3XP:
	case SAA7134_BOARD_ECS_TVP3XP_4CB5:
	case SAA7134_BOARD_ECS_TVP3XP_4CB6:
	case SAA7134_BOARD_MD2819:
	case SAA7134_BOARD_KWORLD_VSTREAM_XPERT:
	case SAA7134_BOARD_KWORLD_XPERT:
	case SAA7134_BOARD_AVERMEDIA_STUDIO_305:
	case SAA7134_BOARD_AVERMEDIA_305:
	case SAA7134_BOARD_AVERMEDIA_STUDIO_505:
	case SAA7134_BOARD_AVERMEDIA_505:
	case SAA7134_BOARD_AVERMEDIA_STUDIO_307:
	case SAA7134_BOARD_AVERMEDIA_307:
	case SAA7134_BOARD_AVERMEDIA_STUDIO_507:
	case SAA7134_BOARD_AVERMEDIA_GO_007_FM:
	case SAA7134_BOARD_AVERMEDIA_777:
	case SAA7134_BOARD_AVERMEDIA_M135A:
/*      case SAA7134_BOARD_SABRENT_SBTTVFM:  */ /* not finished yet */
	case SAA7134_BOARD_VIDEOMATE_TV_PVR:
	case SAA7134_BOARD_VIDEOMATE_GOLD_PLUS:
	case SAA7134_BOARD_VIDEOMATE_TV_GOLD_PLUSII:
	case SAA7134_BOARD_VIDEOMATE_M1F:
	case SAA7134_BOARD_VIDEOMATE_DVBT_300:
	case SAA7134_BOARD_VIDEOMATE_DVBT_200:
	case SAA7134_BOARD_VIDEOMATE_DVBT_200A:
	case SAA7134_BOARD_MANLI_MTV001:
	case SAA7134_BOARD_MANLI_MTV002:
	case SAA7134_BOARD_BEHOLD_409FM:
	case SAA7134_BOARD_AVACSSMARTTV:
	case SAA7134_BOARD_GOTVIEW_7135:
	case SAA7134_BOARD_KWORLD_TERMINATOR:
	case SAA7134_BOARD_SEDNA_PC_TV_CARDBUS:
	case SAA7134_BOARD_FLYDVBT_LR301:
	case SAA7134_BOARD_ASUSTeK_PS3_100:
	case SAA7134_BOARD_ASUSTeK_P7131_DUAL:
	case SAA7134_BOARD_ASUSTeK_P7131_HYBRID_LNA:
	case SAA7134_BOARD_ASUSTeK_P7131_ANALOG:
	case SAA7134_BOARD_FLYDVBTDUO:
	case SAA7134_BOARD_PROTEUS_2309:
	case SAA7134_BOARD_AVERMEDIA_A16AR:
	case SAA7134_BOARD_ENCORE_ENLTV:
	case SAA7134_BOARD_ENCORE_ENLTV_FM:
	case SAA7134_BOARD_ENCORE_ENLTV_FM53:
	case SAA7134_BOARD_ENCORE_ENLTV_FM3:
	case SAA7134_BOARD_10MOONSTVMASTER3:
	case SAA7134_BOARD_BEHOLD_401:
	case SAA7134_BOARD_BEHOLD_403:
	case SAA7134_BOARD_BEHOLD_403FM:
	case SAA7134_BOARD_BEHOLD_405:
	case SAA7134_BOARD_BEHOLD_405FM:
	case SAA7134_BOARD_BEHOLD_407:
	case SAA7134_BOARD_BEHOLD_407FM:
	case SAA7134_BOARD_BEHOLD_409:
	case SAA7134_BOARD_BEHOLD_505FM:
	case SAA7134_BOARD_BEHOLD_505RDS_MK5:
	case SAA7134_BOARD_BEHOLD_505RDS_MK3:
	case SAA7134_BOARD_BEHOLD_507_9FM:
	case SAA7134_BOARD_BEHOLD_507RDS_MK3:
	case SAA7134_BOARD_BEHOLD_507RDS_MK5:
	case SAA7134_BOARD_GENIUS_TVGO_A11MCE:
	case SAA7134_BOARD_REAL_ANGEL_220:
	case SAA7134_BOARD_KWORLD_PLUS_TV_ANALOG:
	case SAA7134_BOARD_AVERMEDIA_GO_007_FM_PLUS:
	case SAA7134_BOARD_ROVERMEDIA_LINK_PRO_FM:
	case SAA7134_BOARD_LEADTEK_WINFAST_DTV1000S:
	case SAA7134_BOARD_LEADTEK_WINFAST_TV2100_FM:
		dev->has_remote = SAA7134_REMOTE_GPIO;
		break;
	case SAA7134_BOARD_FLYDVBS_LR300:
		saa_writeb(SAA7134_GPIO_GPMODE3, 0x80);
		saa_writeb(SAA7134_GPIO_GPSTATUS2, 0x40);
		dev->has_remote = SAA7134_REMOTE_GPIO;
		break;
	case SAA7134_BOARD_MD5044:
		pr_warn("%s: seems there are two different versions of the MD5044\n"
			"%s: (with the same ID) out there.  If sound doesn't work for\n"
			"%s: you try the audio_clock_override=0x200000 insmod option.\n",
			dev->name, dev->name, dev->name);
		break;
	case SAA7134_BOARD_CINERGY400_CARDBUS:
		/* power-up tuner chip */
		saa_andorl(SAA7134_GPIO_GPMODE0 >> 2,   0x00040000, 0x00040000);
		saa_andorl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x00040000, 0x00000000);
		break;
	case SAA7134_BOARD_PINNACLE_300I_DVBT_PAL:
		/* this turns the remote control chip off to work around a bug in it */
		saa_writeb(SAA7134_GPIO_GPMODE1, 0x80);
		saa_writeb(SAA7134_GPIO_GPSTATUS1, 0x80);
		break;
	case SAA7134_BOARD_MONSTERTV_MOBILE:
		/* power-up tuner chip */
		saa_andorl(SAA7134_GPIO_GPMODE0 >> 2,   0x00040000, 0x00040000);
		saa_andorl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x00040000, 0x00000004);
		break;
	case SAA7134_BOARD_FLYDVBT_DUO_CARDBUS:
		/* turn the fan on */
		saa_writeb(SAA7134_GPIO_GPMODE3, 0x08);
		saa_writeb(SAA7134_GPIO_GPSTATUS3, 0x06);
		break;
	case SAA7134_BOARD_ADS_DUO_CARDBUS_PTV331:
	case SAA7134_BOARD_FLYDVBT_HYBRID_CARDBUS:
		saa_andorl(SAA7134_GPIO_GPMODE0 >> 2, 0x08000000, 0x08000000);
		saa_andorl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x08000000, 0x00000000);
		break;
	case SAA7134_BOARD_AVERMEDIA_CARDBUS:
	case SAA7134_BOARD_AVERMEDIA_M115:
		/* power-down tuner chip */
		saa_andorl(SAA7134_GPIO_GPMODE0 >> 2,   0xffffffff, 0);
		saa_andorl(SAA7134_GPIO_GPSTATUS0 >> 2, 0xffffffff, 0);
		msleep(10);
		/* power-up tuner chip */
		saa_andorl(SAA7134_GPIO_GPMODE0 >> 2,   0xffffffff, 0xffffffff);
		saa_andorl(SAA7134_GPIO_GPSTATUS0 >> 2, 0xffffffff, 0xffffffff);
		msleep(10);
		break;
	case SAA7134_BOARD_AVERMEDIA_CARDBUS_501:
		/* power-down tuner chip */
		saa_andorl(SAA7134_GPIO_GPMODE0 >> 2,   0x08400000, 0x08400000);
		saa_andorl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x08400000, 0);
		msleep(10);
		saa_andorl(SAA7134_GPIO_GPMODE0 >> 2,   0x08400000, 0x08400000);
		saa_andorl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x08400000, 0x08400000);
		msleep(10);
		dev->has_remote = SAA7134_REMOTE_I2C;
		break;
	case SAA7134_BOARD_AVERMEDIA_CARDBUS_506:
		saa7134_set_gpio(dev, 23, 0);
		msleep(10);
		saa7134_set_gpio(dev, 23, 1);
		dev->has_remote = SAA7134_REMOTE_I2C;
		break;
	case SAA7134_BOARD_AVERMEDIA_M103:
		saa7134_set_gpio(dev, 23, 0);
		msleep(10);
		saa7134_set_gpio(dev, 23, 1);
		break;
	case SAA7134_BOARD_AVERMEDIA_A16D:
		saa7134_set_gpio(dev, 21, 0);
		msleep(10);
		saa7134_set_gpio(dev, 21, 1);
		msleep(1);
		dev->has_remote = SAA7134_REMOTE_GPIO;
		break;
	case SAA7134_BOARD_BEHOLD_COLUMBUS_TVFM:
		/* power-down tuner chip */
		saa_andorl(SAA7134_GPIO_GPMODE0 >> 2,   0x000A8004, 0x000A8004);
		saa_andorl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x000A8004, 0);
		msleep(10);
		/* power-up tuner chip */
		saa_andorl(SAA7134_GPIO_GPMODE0 >> 2,   0x000A8004, 0x000A8004);
		saa_andorl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x000A8004, 0x000A8004);
		msleep(10);
		/* remote via GPIO */
		dev->has_remote = SAA7134_REMOTE_GPIO;
		break;
	case SAA7134_BOARD_RTD_VFG7350:

		/*
		 * Make sure Production Test Register at offset 0x1D1 is cleared
		 * to take chip out of test mode.  Clearing bit 4 (TST_EN_AOUT)
		 * prevents pin 105 from remaining low; keeping pin 105 low
		 * continually resets the SAA6752 chip.
		 */

		saa_writeb (SAA7134_PRODUCTION_TEST_MODE, 0x00);
		break;
	case SAA7134_BOARD_HAUPPAUGE_HVR1150:
	case SAA7134_BOARD_HAUPPAUGE_HVR1120:
		dev->has_remote = SAA7134_REMOTE_GPIO;
		/* GPIO 26 high for digital, low for analog */
		saa7134_set_gpio(dev, 26, 0);
		msleep(1);

		saa7134_set_gpio(dev, 22, 0);
		msleep(10);
		saa7134_set_gpio(dev, 22, 1);
		break;
	/* i2c remotes */
	case SAA7134_BOARD_PINNACLE_PCTV_110i:
	case SAA7134_BOARD_PINNACLE_PCTV_310i:
	case SAA7134_BOARD_UPMOST_PURPLE_TV:
	case SAA7134_BOARD_MSI_TVATANYWHERE_PLUS:
	case SAA7134_BOARD_HAUPPAUGE_HVR1110:
	case SAA7134_BOARD_BEHOLD_607FM_MK3:
	case SAA7134_BOARD_BEHOLD_607FM_MK5:
	case SAA7134_BOARD_BEHOLD_609FM_MK3:
	case SAA7134_BOARD_BEHOLD_609FM_MK5:
	case SAA7134_BOARD_BEHOLD_607RDS_MK3:
	case SAA7134_BOARD_BEHOLD_607RDS_MK5:
	case SAA7134_BOARD_BEHOLD_609RDS_MK3:
	case SAA7134_BOARD_BEHOLD_609RDS_MK5:
	case SAA7134_BOARD_BEHOLD_M6:
	case SAA7134_BOARD_BEHOLD_M63:
	case SAA7134_BOARD_BEHOLD_M6_EXTRA:
	case SAA7134_BOARD_BEHOLD_H6:
	case SAA7134_BOARD_BEHOLD_X7:
	case SAA7134_BOARD_BEHOLD_H7:
	case SAA7134_BOARD_BEHOLD_A7:
	case SAA7134_BOARD_KWORLD_PC150U:
	case SAA7134_BOARD_SNAZIO_TVPVR_PRO:
		dev->has_remote = SAA7134_REMOTE_I2C;
		break;
	case SAA7134_BOARD_AVERMEDIA_A169_B:
		pr_warn("%s: %s: dual saa713x broadcast decoders\n"
			"%s: Sorry, none of the inputs to this chip are supported yet.\n"
			"%s: Dual decoder functionality is disabled for now, use the other chip.\n",
			dev->name, card(dev).name, dev->name, dev->name);
		break;
	case SAA7134_BOARD_AVERMEDIA_M102:
		/* enable tuner */
	       dev->has_remote = SAA7134_REMOTE_GPIO;
		saa_andorl(SAA7134_GPIO_GPMODE0 >> 2,   0x8c040007, 0x8c040007);
		saa_andorl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x0c0007cd, 0x0c0007cd);
		break;
	case SAA7134_BOARD_AVERMEDIA_A700_HYBRID:
	case SAA7134_BOARD_AVERMEDIA_A700_PRO:
		/* write windows gpio values */
		saa_andorl(SAA7134_GPIO_GPMODE0 >> 2,   0x80040100, 0x80040100);
		saa_andorl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x80040100, 0x00040100);
		break;
	case SAA7134_BOARD_AVERMEDIA_A706:
		/* radio antenna select: tristate both as in Windows driver */
		saa7134_set_gpio(dev, 12, 3);	/* TV antenna */
		saa7134_set_gpio(dev, 13, 3);	/* FM antenna */
		dev->has_remote = SAA7134_REMOTE_I2C;
		/*
		 * Disable CE5039 DVB-S tuner now (SLEEP pin high) to prevent
		 * it from interfering with analog tuner detection
		 */
		saa7134_set_gpio(dev, 23, 1);
		break;
	case SAA7134_BOARD_VIDEOMATE_S350:
		dev->has_remote = SAA7134_REMOTE_GPIO;
		saa_andorl(SAA7134_GPIO_GPMODE0 >> 2,   0x0000C000, 0x0000C000);
		saa_andorl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x0000C000, 0x0000C000);
		break;
	case SAA7134_BOARD_AVERMEDIA_M733A:
		saa7134_set_gpio(dev, 1, 1);
		msleep(10);
		saa7134_set_gpio(dev, 1, 0);
		msleep(10);
		saa7134_set_gpio(dev, 1, 1);
		dev->has_remote = SAA7134_REMOTE_GPIO;
		break;
	case SAA7134_BOARD_MAGICPRO_PROHDTV_PRO2:
		/* enable LGS-8G75 */
		saa_andorl(SAA7134_GPIO_GPMODE0 >> 2,   0x0e050000, 0x0c050000);
		saa_andorl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x0e050000, 0x0c050000);
		break;
	case SAA7134_BOARD_VIDEOMATE_T750:
		/* enable the analog tuner */
		saa_andorl(SAA7134_GPIO_GPMODE0 >> 2,   0x00008000, 0x00008000);
		saa_andorl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x00008000, 0x00008000);
		break;
	}
	return 0;
}