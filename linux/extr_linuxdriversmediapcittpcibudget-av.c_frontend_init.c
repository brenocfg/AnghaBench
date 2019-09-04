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
struct saa7146_dev {TYPE_3__* pci; void* i2c_bitrate; } ;
struct TYPE_5__ {void* set_params; int /*<<< orphan*/  init; } ;
struct TYPE_6__ {TYPE_1__ tuner_ops; } ;
struct dvb_frontend {TYPE_2__ ops; } ;
struct TYPE_8__ {struct dvb_frontend* dvb_frontend; int /*<<< orphan*/  dvb_adapter; int /*<<< orphan*/  i2c_adap; struct saa7146_dev* dev; } ;
struct budget_av {int reinitialise_demod; TYPE_4__ budget; } ;
struct TYPE_7__ {int subsystem_device; int subsystem_vendor; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVB_PLL_PHILIPS_SD1878_TDA8261 ; 
 int /*<<< orphan*/  SAA7146_GPIO_OUTHI ; 
 int /*<<< orphan*/  SAA7146_GPIO_OUTLO ; 
 void* SAA7146_I2C_BUS_BIT_RATE_240 ; 
#define  SUBID_DVBC_CINERGY1200 154 
#define  SUBID_DVBC_CINERGY1200_MK3 153 
#define  SUBID_DVBC_EASYWATCH 152 
#define  SUBID_DVBC_EASYWATCH_MK3 151 
#define  SUBID_DVBC_KNC1 150 
#define  SUBID_DVBC_KNC1_MK3 149 
#define  SUBID_DVBC_KNC1_PLUS 148 
#define  SUBID_DVBC_KNC1_PLUS_MK3 147 
#define  SUBID_DVBC_KNC1_TDA10024 146 
#define  SUBID_DVBS2_EASYWATCH 145 
#define  SUBID_DVBS2_KNC1 144 
#define  SUBID_DVBS2_KNC1_OEM 143 
#define  SUBID_DVBS_CINERGY1200 142 
#define  SUBID_DVBS_CYNERGY1200N 141 
#define  SUBID_DVBS_EASYWATCH 140 
#define  SUBID_DVBS_EASYWATCH_1 139 
#define  SUBID_DVBS_EASYWATCH_2 138 
#define  SUBID_DVBS_KNC1 137 
#define  SUBID_DVBS_KNC1_PLUS 136 
#define  SUBID_DVBS_TV_STAR 135 
#define  SUBID_DVBS_TV_STAR_CI 134 
#define  SUBID_DVBS_TV_STAR_PLUS_X4 133 
#define  SUBID_DVBS_TYPHOON 132 
#define  SUBID_DVBT_CINERGY1200 131 
#define  SUBID_DVBT_EASYWATCH 130 
#define  SUBID_DVBT_KNC1 129 
#define  SUBID_DVBT_KNC1_PLUS 128 
 int /*<<< orphan*/  cinergy_1200s_1894_0010_config ; 
 int /*<<< orphan*/  cinergy_1200s_config ; 
 struct dvb_frontend* dvb_attach (int /*<<< orphan*/ ,struct dvb_frontend*,int,...) ; 
 int /*<<< orphan*/  dvb_frontend_detach (struct dvb_frontend*) ; 
 int /*<<< orphan*/  dvb_pll_attach ; 
 scalar_t__ dvb_register_frontend (int /*<<< orphan*/ *,struct dvb_frontend*) ; 
 int /*<<< orphan*/  knc1_dvbs2_config ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  philips_cu1216_config ; 
 int /*<<< orphan*/  philips_cu1216_config_altaddress ; 
 int /*<<< orphan*/  philips_cu1216_tda10023_config ; 
 void* philips_cu1216_tuner_set_params ; 
 int /*<<< orphan*/  philips_sd1878_config ; 
 void* philips_su1278_ty_ci_tuner_set_params ; 
 int /*<<< orphan*/  philips_tu1216_config ; 
 int /*<<< orphan*/  philips_tu1216_tuner_init ; 
 void* philips_tu1216_tuner_set_params ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  read_pwm (struct budget_av*) ; 
 int /*<<< orphan*/  saa7146_setgpio (struct saa7146_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd1878c_config ; 
 int /*<<< orphan*/  stb0899_attach ; 
 int /*<<< orphan*/  stv0299_attach ; 
 int /*<<< orphan*/  tda10021_attach ; 
 int /*<<< orphan*/  tda10023_attach ; 
 int /*<<< orphan*/  tda10046_attach ; 
 int /*<<< orphan*/  tda8261_attach ; 
 int /*<<< orphan*/  tua6100_attach ; 
 int /*<<< orphan*/  typhoon_config ; 

__attribute__((used)) static void frontend_init(struct budget_av *budget_av)
{
	struct saa7146_dev * saa = budget_av->budget.dev;
	struct dvb_frontend * fe = NULL;

	/* Enable / PowerON Frontend */
	saa7146_setgpio(saa, 0, SAA7146_GPIO_OUTLO);

	/* Wait for PowerON */
	msleep(100);

	/* additional setup necessary for the PLUS cards */
	switch (saa->pci->subsystem_device) {
		case SUBID_DVBS_KNC1_PLUS:
		case SUBID_DVBC_KNC1_PLUS:
		case SUBID_DVBT_KNC1_PLUS:
		case SUBID_DVBC_EASYWATCH:
		case SUBID_DVBC_KNC1_PLUS_MK3:
		case SUBID_DVBS2_KNC1:
		case SUBID_DVBS2_KNC1_OEM:
		case SUBID_DVBS2_EASYWATCH:
			saa7146_setgpio(saa, 3, SAA7146_GPIO_OUTHI);
			break;
	}

	switch (saa->pci->subsystem_device) {

	case SUBID_DVBS_KNC1:
		/*
		 * maybe that setting is needed for other dvb-s cards as well,
		 * but so far it has been only confirmed for this type
		 */
		budget_av->reinitialise_demod = 1;
		/* fall through */
	case SUBID_DVBS_KNC1_PLUS:
	case SUBID_DVBS_EASYWATCH_1:
		if (saa->pci->subsystem_vendor == 0x1894) {
			fe = dvb_attach(stv0299_attach, &cinergy_1200s_1894_0010_config,
					     &budget_av->budget.i2c_adap);
			if (fe) {
				dvb_attach(tua6100_attach, fe, 0x60, &budget_av->budget.i2c_adap);
			}
		} else {
			fe = dvb_attach(stv0299_attach, &typhoon_config,
					     &budget_av->budget.i2c_adap);
			if (fe) {
				fe->ops.tuner_ops.set_params = philips_su1278_ty_ci_tuner_set_params;
			}
		}
		break;

	case SUBID_DVBS_TV_STAR:
	case SUBID_DVBS_TV_STAR_PLUS_X4:
	case SUBID_DVBS_TV_STAR_CI:
	case SUBID_DVBS_CYNERGY1200N:
	case SUBID_DVBS_EASYWATCH:
	case SUBID_DVBS_EASYWATCH_2:
		fe = dvb_attach(stv0299_attach, &philips_sd1878_config,
				&budget_av->budget.i2c_adap);
		if (fe) {
			dvb_attach(dvb_pll_attach, fe, 0x60,
				   &budget_av->budget.i2c_adap,
				   DVB_PLL_PHILIPS_SD1878_TDA8261);
		}
		break;

	case SUBID_DVBS_TYPHOON:
		fe = dvb_attach(stv0299_attach, &typhoon_config,
				    &budget_av->budget.i2c_adap);
		if (fe) {
			fe->ops.tuner_ops.set_params = philips_su1278_ty_ci_tuner_set_params;
		}
		break;
	case SUBID_DVBS2_KNC1:
	case SUBID_DVBS2_KNC1_OEM:
	case SUBID_DVBS2_EASYWATCH:
		budget_av->reinitialise_demod = 1;
		if ((fe = dvb_attach(stb0899_attach, &knc1_dvbs2_config, &budget_av->budget.i2c_adap)))
			dvb_attach(tda8261_attach, fe, &sd1878c_config, &budget_av->budget.i2c_adap);

		break;
	case SUBID_DVBS_CINERGY1200:
		fe = dvb_attach(stv0299_attach, &cinergy_1200s_config,
				    &budget_av->budget.i2c_adap);
		if (fe) {
			fe->ops.tuner_ops.set_params = philips_su1278_ty_ci_tuner_set_params;
		}
		break;

	case SUBID_DVBC_KNC1:
	case SUBID_DVBC_KNC1_PLUS:
	case SUBID_DVBC_CINERGY1200:
	case SUBID_DVBC_EASYWATCH:
		budget_av->reinitialise_demod = 1;
		budget_av->budget.dev->i2c_bitrate = SAA7146_I2C_BUS_BIT_RATE_240;
		fe = dvb_attach(tda10021_attach, &philips_cu1216_config,
				     &budget_av->budget.i2c_adap,
				     read_pwm(budget_av));
		if (fe == NULL)
			fe = dvb_attach(tda10021_attach, &philips_cu1216_config_altaddress,
					     &budget_av->budget.i2c_adap,
					     read_pwm(budget_av));
		if (fe) {
			fe->ops.tuner_ops.set_params = philips_cu1216_tuner_set_params;
		}
		break;

	case SUBID_DVBC_EASYWATCH_MK3:
	case SUBID_DVBC_CINERGY1200_MK3:
	case SUBID_DVBC_KNC1_MK3:
	case SUBID_DVBC_KNC1_TDA10024:
	case SUBID_DVBC_KNC1_PLUS_MK3:
		budget_av->reinitialise_demod = 1;
		budget_av->budget.dev->i2c_bitrate = SAA7146_I2C_BUS_BIT_RATE_240;
		fe = dvb_attach(tda10023_attach,
			&philips_cu1216_tda10023_config,
			&budget_av->budget.i2c_adap,
			read_pwm(budget_av));
		if (fe) {
			fe->ops.tuner_ops.set_params = philips_cu1216_tuner_set_params;
		}
		break;

	case SUBID_DVBT_EASYWATCH:
	case SUBID_DVBT_KNC1:
	case SUBID_DVBT_KNC1_PLUS:
	case SUBID_DVBT_CINERGY1200:
		budget_av->reinitialise_demod = 1;
		fe = dvb_attach(tda10046_attach, &philips_tu1216_config,
				     &budget_av->budget.i2c_adap);
		if (fe) {
			fe->ops.tuner_ops.init = philips_tu1216_tuner_init;
			fe->ops.tuner_ops.set_params = philips_tu1216_tuner_set_params;
		}
		break;
	}

	if (fe == NULL) {
		pr_err("A frontend driver was not found for device [%04x:%04x] subsystem [%04x:%04x]\n",
		       saa->pci->vendor,
		       saa->pci->device,
		       saa->pci->subsystem_vendor,
		       saa->pci->subsystem_device);
		return;
	}

	budget_av->budget.dvb_frontend = fe;

	if (dvb_register_frontend(&budget_av->budget.dvb_adapter,
				  budget_av->budget.dvb_frontend)) {
		pr_err("Frontend registration failed!\n");
		dvb_frontend_detach(budget_av->budget.dvb_frontend);
		budget_av->budget.dvb_frontend = NULL;
	}
}