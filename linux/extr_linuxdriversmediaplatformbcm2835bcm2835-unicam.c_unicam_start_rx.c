#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int height; int /*<<< orphan*/  bytesperline; } ;
struct TYPE_5__ {TYPE_1__ pix; } ;
struct TYPE_6__ {TYPE_2__ fmt; } ;
struct unicam_cfg {int dummy; } ;
struct unicam_device {unsigned int active_data_lanes; scalar_t__ bus_type; int bus_flags; int max_data_lanes; TYPE_3__ v_fmt; struct unicam_cfg cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNICAM_ANA ; 
 int UNICAM_AR ; 
 int /*<<< orphan*/  UNICAM_BL_MASK ; 
 int /*<<< orphan*/  UNICAM_BS_MASK ; 
 int /*<<< orphan*/  UNICAM_CLE ; 
 int /*<<< orphan*/  UNICAM_CLHSE ; 
 int /*<<< orphan*/  UNICAM_CLK ; 
 int /*<<< orphan*/  UNICAM_CLLPE ; 
 int /*<<< orphan*/  UNICAM_CLT ; 
 int UNICAM_CLT1_MASK ; 
 int UNICAM_CLT2_MASK ; 
 int /*<<< orphan*/  UNICAM_CLTRE ; 
 int /*<<< orphan*/  UNICAM_CMP0 ; 
 int UNICAM_CPE ; 
 int /*<<< orphan*/  UNICAM_CPH ; 
 int UNICAM_CPM_CCP2 ; 
 int UNICAM_CPM_CSI2 ; 
 int /*<<< orphan*/  UNICAM_CPM_MASK ; 
 int UNICAM_CPR ; 
 int /*<<< orphan*/  UNICAM_CTATADJ_MASK ; 
 int /*<<< orphan*/  UNICAM_CTRL ; 
 int /*<<< orphan*/  UNICAM_DAT0 ; 
 int /*<<< orphan*/  UNICAM_DAT1 ; 
 int /*<<< orphan*/  UNICAM_DAT2 ; 
 int /*<<< orphan*/  UNICAM_DAT3 ; 
 int /*<<< orphan*/  UNICAM_DCM_MASK ; 
 int UNICAM_DCM_STROBE ; 
 int /*<<< orphan*/  UNICAM_DCS ; 
 int UNICAM_DDL ; 
 int /*<<< orphan*/  UNICAM_DLE ; 
 int /*<<< orphan*/  UNICAM_DLHSE ; 
 int /*<<< orphan*/  UNICAM_DLLPE ; 
 int /*<<< orphan*/  UNICAM_DLT ; 
 int UNICAM_DLT1_MASK ; 
 int UNICAM_DLT2_MASK ; 
 int UNICAM_DLT3_MASK ; 
 int /*<<< orphan*/  UNICAM_DLTRE ; 
 int /*<<< orphan*/  UNICAM_EDL_MASK ; 
 int UNICAM_FCM ; 
 int UNICAM_FEIE ; 
 int /*<<< orphan*/  UNICAM_FL0 ; 
 int /*<<< orphan*/  UNICAM_FL1 ; 
 int UNICAM_FSIE ; 
 int /*<<< orphan*/  UNICAM_GI ; 
 int /*<<< orphan*/  UNICAM_ICTL ; 
 int /*<<< orphan*/  UNICAM_IHWIN ; 
 int /*<<< orphan*/  UNICAM_ISTA ; 
 int UNICAM_ISTA_MASK_ALL ; 
 int /*<<< orphan*/  UNICAM_IVWIN ; 
 int /*<<< orphan*/  UNICAM_LCIE_MASK ; 
 int UNICAM_LIP_MASK ; 
 int UNICAM_MEM ; 
 int /*<<< orphan*/  UNICAM_MISC ; 
 int /*<<< orphan*/  UNICAM_NP_MASK ; 
 int /*<<< orphan*/  UNICAM_OET_MASK ; 
 int /*<<< orphan*/  UNICAM_PCDT_MASK ; 
 int /*<<< orphan*/  UNICAM_PCE ; 
 int /*<<< orphan*/  UNICAM_PCVC_MASK ; 
 int /*<<< orphan*/  UNICAM_PE ; 
 int /*<<< orphan*/  UNICAM_PFT_MASK ; 
 int /*<<< orphan*/  UNICAM_PP_MASK ; 
 int /*<<< orphan*/  UNICAM_PRI ; 
 int /*<<< orphan*/  UNICAM_PTATADJ_MASK ; 
 int /*<<< orphan*/  UNICAM_PT_MASK ; 
 int UNICAM_SOE ; 
 int /*<<< orphan*/  UNICAM_STA ; 
 int UNICAM_STA_MASK_ALL ; 
 int UNICAM_TFC ; 
 scalar_t__ V4L2_MBUS_CSI2 ; 
 int V4L2_MBUS_CSI2_CONTINUOUS_CLOCK ; 
 int /*<<< orphan*/  clk_write (struct unicam_cfg*,int) ; 
 int reg_read (struct unicam_cfg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct unicam_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_write_field (struct unicam_cfg*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_field (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unicam_cfg_image_id (struct unicam_device*) ; 
 int /*<<< orphan*/  unicam_set_packing_config (struct unicam_device*) ; 
 int /*<<< orphan*/  unicam_wr_dma_addr (struct unicam_device*,unsigned long) ; 
 int /*<<< orphan*/  unicam_wr_dma_config (struct unicam_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void unicam_start_rx(struct unicam_device *dev, unsigned long addr)
{
	struct unicam_cfg *cfg = &dev->cfg;
	int line_int_freq = dev->v_fmt.fmt.pix.height >> 2;
	unsigned int i;
	u32 val;

	if (line_int_freq < 128)
		line_int_freq = 128;

	/* Enable lane clocks */
	val = 1;
	for (i = 0; i < dev->active_data_lanes; i++)
		val = val << 2 | 1;
	clk_write(cfg, val);

	/* Basic init */
	reg_write(cfg, UNICAM_CTRL, UNICAM_MEM);

	/* Enable analogue control, and leave in reset. */
	val = UNICAM_AR;
	set_field(&val, 7, UNICAM_CTATADJ_MASK);
	set_field(&val, 7, UNICAM_PTATADJ_MASK);
	reg_write(cfg, UNICAM_ANA, val);
	usleep_range(1000, 2000);

	/* Come out of reset */
	reg_write_field(cfg, UNICAM_ANA, 0, UNICAM_AR);

	/* Peripheral reset */
	reg_write_field(cfg, UNICAM_CTRL, 1, UNICAM_CPR);
	reg_write_field(cfg, UNICAM_CTRL, 0, UNICAM_CPR);

	reg_write_field(cfg, UNICAM_CTRL, 0, UNICAM_CPE);

	/* Enable Rx control. */
	val = reg_read(cfg, UNICAM_CTRL);
	if (dev->bus_type == V4L2_MBUS_CSI2) {
		set_field(&val, UNICAM_CPM_CSI2, UNICAM_CPM_MASK);
		set_field(&val, UNICAM_DCM_STROBE, UNICAM_DCM_MASK);
	} else {
		set_field(&val, UNICAM_CPM_CCP2, UNICAM_CPM_MASK);
		set_field(&val, dev->bus_flags, UNICAM_DCM_MASK);
	}
	/* Packet framer timeout */
	set_field(&val, 0xf, UNICAM_PFT_MASK);
	set_field(&val, 128, UNICAM_OET_MASK);
	reg_write(cfg, UNICAM_CTRL, val);

	reg_write(cfg, UNICAM_IHWIN, 0);
	reg_write(cfg, UNICAM_IVWIN, 0);

	/* AXI bus access QoS setup */
	val = reg_read(&dev->cfg, UNICAM_PRI);
	set_field(&val, 0, UNICAM_BL_MASK);
	set_field(&val, 0, UNICAM_BS_MASK);
	set_field(&val, 0xe, UNICAM_PP_MASK);
	set_field(&val, 8, UNICAM_NP_MASK);
	set_field(&val, 2, UNICAM_PT_MASK);
	set_field(&val, 1, UNICAM_PE);
	reg_write(cfg, UNICAM_PRI, val);

	reg_write_field(cfg, UNICAM_ANA, 0, UNICAM_DDL);

	/* Always start in trigger frame capture mode (UNICAM_FCM set) */
	val = UNICAM_FSIE | UNICAM_FEIE | UNICAM_FCM;
	set_field(&val,  line_int_freq, UNICAM_LCIE_MASK);
	reg_write(cfg, UNICAM_ICTL, val);
	reg_write(cfg, UNICAM_STA, UNICAM_STA_MASK_ALL);
	reg_write(cfg, UNICAM_ISTA, UNICAM_ISTA_MASK_ALL);

	/* tclk_term_en */
	reg_write_field(cfg, UNICAM_CLT, 2, UNICAM_CLT1_MASK);
	/* tclk_settle */
	reg_write_field(cfg, UNICAM_CLT, 6, UNICAM_CLT2_MASK);
	/* td_term_en */
	reg_write_field(cfg, UNICAM_DLT, 2, UNICAM_DLT1_MASK);
	/* ths_settle */
	reg_write_field(cfg, UNICAM_DLT, 6, UNICAM_DLT2_MASK);
	/* trx_enable */
	reg_write_field(cfg, UNICAM_DLT, 0, UNICAM_DLT3_MASK);

	reg_write_field(cfg, UNICAM_CTRL, 0, UNICAM_SOE);

	/* Packet compare setup - required to avoid missing frame ends */
	val = 0;
	set_field(&val, 1, UNICAM_PCE);
	set_field(&val, 1, UNICAM_GI);
	set_field(&val, 1, UNICAM_CPH);
	set_field(&val, 0, UNICAM_PCVC_MASK);
	set_field(&val, 1, UNICAM_PCDT_MASK);
	reg_write(cfg, UNICAM_CMP0, val);

	/* Enable clock lane and set up terminations */
	val = 0;
	if (dev->bus_type == V4L2_MBUS_CSI2) {
		/* CSI2 */
		set_field(&val, 1, UNICAM_CLE);
		set_field(&val, 1, UNICAM_CLLPE);
		if (dev->bus_flags & V4L2_MBUS_CSI2_CONTINUOUS_CLOCK) {
			set_field(&val, 1, UNICAM_CLTRE);
			set_field(&val, 1, UNICAM_CLHSE);
		}
	} else {
		/* CCP2 */
		set_field(&val, 1, UNICAM_CLE);
		set_field(&val, 1, UNICAM_CLHSE);
		set_field(&val, 1, UNICAM_CLTRE);
	}
	reg_write(cfg, UNICAM_CLK, val);

	/*
	 * Enable required data lanes with appropriate terminations.
	 * The same value needs to be written to UNICAM_DATn registers for
	 * the active lanes, and 0 for inactive ones.
	 */
	val = 0;
	if (dev->bus_type == V4L2_MBUS_CSI2) {
		/* CSI2 */
		set_field(&val, 1, UNICAM_DLE);
		set_field(&val, 1, UNICAM_DLLPE);
		if (dev->bus_flags & V4L2_MBUS_CSI2_CONTINUOUS_CLOCK) {
			set_field(&val, 1, UNICAM_DLTRE);
			set_field(&val, 1, UNICAM_DLHSE);
		}
	} else {
		/* CCP2 */
		set_field(&val, 1, UNICAM_DLE);
		set_field(&val, 1, UNICAM_DLHSE);
		set_field(&val, 1, UNICAM_DLTRE);
	}
	reg_write(cfg, UNICAM_DAT0, val);

	if (dev->active_data_lanes == 1)
		val = 0;
	reg_write(cfg, UNICAM_DAT1, val);

	if (dev->max_data_lanes > 2) {
		/*
		 * Registers UNICAM_DAT2 and UNICAM_DAT3 only valid if the
		 * instance supports more than 2 data lanes.
		 */
		if (dev->active_data_lanes == 2)
			val = 0;
		reg_write(cfg, UNICAM_DAT2, val);

		if (dev->active_data_lanes == 3)
			val = 0;
		reg_write(cfg, UNICAM_DAT3, val);
	}

	unicam_wr_dma_config(dev, dev->v_fmt.fmt.pix.bytesperline);
	unicam_wr_dma_addr(dev, addr);
	unicam_set_packing_config(dev);
	unicam_cfg_image_id(dev);

	/* Disabled embedded data */
	val = 0;
	set_field(&val, 0, UNICAM_EDL_MASK);
	reg_write(cfg, UNICAM_DCS, val);

	val = reg_read(cfg, UNICAM_MISC);
	set_field(&val, 1, UNICAM_FL0);
	set_field(&val, 1, UNICAM_FL1);
	reg_write(cfg, UNICAM_MISC, val);

	/* Enable peripheral */
	reg_write_field(cfg, UNICAM_CTRL, 1, UNICAM_CPE);

	/* Load image pointers */
	reg_write_field(cfg, UNICAM_ICTL, 1, UNICAM_LIP_MASK);

	/*
	 * Enable trigger only for the first frame to
	 * sync correctly to the FS from the source.
	 */
	reg_write_field(cfg, UNICAM_ICTL, 1, UNICAM_TFC);
}