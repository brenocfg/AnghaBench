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
struct init_status {int chip_clk; scalar_t__ mem_clk; int master_clk; } ;
struct sm750_dev {int devid; int pnltype; int /*<<< orphan*/  accel_off; scalar_t__ nocrt; struct init_status initParm; } ;
struct pci_dev {int dummy; } ;
struct initchip_param {int dummy; } ;

/* Variables and functions */
 int DEFAULT_SM750LE_CHIP_CLOCK ; 
 int DEFAULT_SM750_CHIP_CLOCK ; 
 int /*<<< orphan*/  MISC_CTRL ; 
 unsigned int MISC_CTRL_DAC_POWER_OFF ; 
 int /*<<< orphan*/  PANEL_DISPLAY_CTRL ; 
 unsigned int PANEL_DISPLAY_CTRL_DOUBLE_PIXEL ; 
 unsigned int PANEL_DISPLAY_CTRL_DUAL_DISPLAY ; 
 scalar_t__ SM750LE ; 
 int /*<<< orphan*/  SYSTEM_CTRL ; 
 unsigned int SYSTEM_CTRL_DPMS_MASK ; 
 unsigned int SYSTEM_CTRL_DPMS_VPHN ; 
 unsigned int SYSTEM_CTRL_DPMS_VPHP ; 
 unsigned int SYSTEM_CTRL_PCI_BURST ; 
 int /*<<< orphan*/  ddk750_init_hw (struct initchip_param*) ; 
 int /*<<< orphan*/  hw_sm750_initAccel (struct sm750_dev*) ; 
 unsigned int peek32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poke32 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
#define  sm750_24TFT 130 
#define  sm750_doubleTFT 129 
#define  sm750_dualTFT 128 
 scalar_t__ sm750_get_chip_type () ; 
 int /*<<< orphan*/  sm750_sw_i2c_init (int /*<<< orphan*/ ,int) ; 
 int sm750_sw_i2c_read_reg (int,int) ; 
 int /*<<< orphan*/  sm750_sw_i2c_write_reg (int,int,int) ; 

int hw_sm750_inithw(struct sm750_dev *sm750_dev, struct pci_dev *pdev)
{
	struct init_status *parm;

	parm = &sm750_dev->initParm;
	if (parm->chip_clk == 0)
		parm->chip_clk = (sm750_get_chip_type() == SM750LE) ?
						DEFAULT_SM750LE_CHIP_CLOCK :
						DEFAULT_SM750_CHIP_CLOCK;

	if (parm->mem_clk == 0)
		parm->mem_clk = parm->chip_clk;
	if (parm->master_clk == 0)
		parm->master_clk = parm->chip_clk / 3;

	ddk750_init_hw((struct initchip_param *)&sm750_dev->initParm);
	/* for sm718, open pci burst */
	if (sm750_dev->devid == 0x718) {
		poke32(SYSTEM_CTRL,
		       peek32(SYSTEM_CTRL) | SYSTEM_CTRL_PCI_BURST);
	}

	if (sm750_get_chip_type() != SM750LE) {
		unsigned int val;
		/* does user need CRT? */
		if (sm750_dev->nocrt) {
			poke32(MISC_CTRL,
			       peek32(MISC_CTRL) | MISC_CTRL_DAC_POWER_OFF);
			/* shut off dpms */
			val = peek32(SYSTEM_CTRL) & ~SYSTEM_CTRL_DPMS_MASK;
			val |= SYSTEM_CTRL_DPMS_VPHN;
			poke32(SYSTEM_CTRL, val);
		} else {
			poke32(MISC_CTRL,
			       peek32(MISC_CTRL) & ~MISC_CTRL_DAC_POWER_OFF);
			/* turn on dpms */
			val = peek32(SYSTEM_CTRL) & ~SYSTEM_CTRL_DPMS_MASK;
			val |= SYSTEM_CTRL_DPMS_VPHP;
			poke32(SYSTEM_CTRL, val);
		}

		val = peek32(PANEL_DISPLAY_CTRL) &
			~(PANEL_DISPLAY_CTRL_DUAL_DISPLAY |
			  PANEL_DISPLAY_CTRL_DOUBLE_PIXEL);
		switch (sm750_dev->pnltype) {
		case sm750_24TFT:
			break;
		case sm750_doubleTFT:
			val |= PANEL_DISPLAY_CTRL_DOUBLE_PIXEL;
			break;
		case sm750_dualTFT:
			val |= PANEL_DISPLAY_CTRL_DUAL_DISPLAY;
			break;
		}
		poke32(PANEL_DISPLAY_CTRL, val);
	} else {
		/*
		 * for 750LE, no DVI chip initialization
		 * makes Monitor no signal
		 *
		 * Set up GPIO for software I2C to program DVI chip in the
		 * Xilinx SP605 board, in order to have video signal.
		 */
		sm750_sw_i2c_init(0, 1);

		/*
		 * Customer may NOT use CH7301 DVI chip, which has to be
		 * initialized differently.
		 */
		if (sm750_sw_i2c_read_reg(0xec, 0x4a) == 0x95) {
			/*
			 * The following register values for CH7301 are from
			 * Chrontel app note and our experiment.
			 */
			pr_info("yes,CH7301 DVI chip found\n");
			sm750_sw_i2c_write_reg(0xec, 0x1d, 0x16);
			sm750_sw_i2c_write_reg(0xec, 0x21, 0x9);
			sm750_sw_i2c_write_reg(0xec, 0x49, 0xC0);
			pr_info("okay,CH7301 DVI chip setup done\n");
		}
	}

	/* init 2d engine */
	if (!sm750_dev->accel_off)
		hw_sm750_initAccel(sm750_dev);

	return 0;
}