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
typedef  int u32 ;
struct mcde {int regs; int /*<<< orphan*/  dev; TYPE_1__* mdsi; } ;
typedef  enum mcde_dsi_formatter { ____Placeholder_mcde_dsi_formatter } mcde_dsi_formatter ;
struct TYPE_2__ {int mode_flags; int format; } ;

/* Variables and functions */
 int MCDE_DSICONF0_CMD8 ; 
 int MCDE_DSICONF0_DCSVID_NOTGEN ; 
 int MCDE_DSICONF0_PACKING_RGB565 ; 
 int MCDE_DSICONF0_PACKING_RGB666 ; 
 int MCDE_DSICONF0_PACKING_RGB666_PACKED ; 
 int MCDE_DSICONF0_PACKING_RGB888 ; 
 int MCDE_DSICONF0_PACKING_SHIFT ; 
 int MCDE_DSICONF0_VID_MODE_VID ; 
 int MCDE_DSIVID0CMDW ; 
 int MCDE_DSIVID0CONF0 ; 
 int MCDE_DSIVID0DELAY0 ; 
 int MCDE_DSIVID0DELAY1 ; 
 int MCDE_DSIVID0FRAME ; 
 int MCDE_DSIVID0PKT ; 
 int MCDE_DSIVID0SYNC ; 
 int MCDE_DSIVID1CMDW ; 
 int MCDE_DSIVID1CONF0 ; 
 int MCDE_DSIVID1DELAY0 ; 
 int MCDE_DSIVID1DELAY1 ; 
 int MCDE_DSIVID1FRAME ; 
 int MCDE_DSIVID1PKT ; 
 int MCDE_DSIVID1SYNC ; 
 int MCDE_DSIVID2CMDW ; 
 int MCDE_DSIVID2CONF0 ; 
 int MCDE_DSIVID2DELAY0 ; 
 int MCDE_DSIVID2DELAY1 ; 
 int MCDE_DSIVID2FRAME ; 
 int MCDE_DSIVID2PKT ; 
 int MCDE_DSIVID2SYNC ; 
 int MCDE_DSIVIDXCMDW_CMDW_CONTINUE_SHIFT ; 
 int MCDE_DSIVIDXCMDW_CMDW_START_SHIFT ; 
#define  MCDE_DSI_FORMATTER_0 134 
#define  MCDE_DSI_FORMATTER_1 133 
#define  MCDE_DSI_FORMATTER_2 132 
 int MIPI_DCS_WRITE_MEMORY_CONTINUE ; 
 int MIPI_DCS_WRITE_MEMORY_START ; 
#define  MIPI_DSI_FMT_RGB565 131 
#define  MIPI_DSI_FMT_RGB666 130 
#define  MIPI_DSI_FMT_RGB666_PACKED 129 
#define  MIPI_DSI_FMT_RGB888 128 
 int MIPI_DSI_MODE_VIDEO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static void mcde_configure_dsi_formatter(struct mcde *mcde,
					 enum mcde_dsi_formatter fmt,
					 u32 formatter_frame,
					 int pkt_size)
{
	u32 val;
	u32 conf0;
	u32 frame;
	u32 pkt;
	u32 sync;
	u32 cmdw;
	u32 delay0, delay1;

	switch (fmt) {
	case MCDE_DSI_FORMATTER_0:
		conf0 = MCDE_DSIVID0CONF0;
		frame = MCDE_DSIVID0FRAME;
		pkt = MCDE_DSIVID0PKT;
		sync = MCDE_DSIVID0SYNC;
		cmdw = MCDE_DSIVID0CMDW;
		delay0 = MCDE_DSIVID0DELAY0;
		delay1 = MCDE_DSIVID0DELAY1;
		break;
	case MCDE_DSI_FORMATTER_1:
		conf0 = MCDE_DSIVID1CONF0;
		frame = MCDE_DSIVID1FRAME;
		pkt = MCDE_DSIVID1PKT;
		sync = MCDE_DSIVID1SYNC;
		cmdw = MCDE_DSIVID1CMDW;
		delay0 = MCDE_DSIVID1DELAY0;
		delay1 = MCDE_DSIVID1DELAY1;
		break;
	case MCDE_DSI_FORMATTER_2:
		conf0 = MCDE_DSIVID2CONF0;
		frame = MCDE_DSIVID2FRAME;
		pkt = MCDE_DSIVID2PKT;
		sync = MCDE_DSIVID2SYNC;
		cmdw = MCDE_DSIVID2CMDW;
		delay0 = MCDE_DSIVID2DELAY0;
		delay1 = MCDE_DSIVID2DELAY1;
		break;
	}

	/*
	 * Enable formatter
	 * 8 bit commands and DCS commands (notgen = not generic)
	 */
	val = MCDE_DSICONF0_CMD8 | MCDE_DSICONF0_DCSVID_NOTGEN;
	if (mcde->mdsi->mode_flags & MIPI_DSI_MODE_VIDEO)
		val |= MCDE_DSICONF0_VID_MODE_VID;
	switch (mcde->mdsi->format) {
	case MIPI_DSI_FMT_RGB888:
		val |= MCDE_DSICONF0_PACKING_RGB888 <<
			MCDE_DSICONF0_PACKING_SHIFT;
		break;
	case MIPI_DSI_FMT_RGB666:
		val |= MCDE_DSICONF0_PACKING_RGB666 <<
			MCDE_DSICONF0_PACKING_SHIFT;
		break;
	case MIPI_DSI_FMT_RGB666_PACKED:
		val |= MCDE_DSICONF0_PACKING_RGB666_PACKED <<
			MCDE_DSICONF0_PACKING_SHIFT;
		break;
	case MIPI_DSI_FMT_RGB565:
		val |= MCDE_DSICONF0_PACKING_RGB565 <<
			MCDE_DSICONF0_PACKING_SHIFT;
		break;
	default:
		dev_err(mcde->dev, "unknown DSI format\n");
		return;
	}
	writel(val, mcde->regs + conf0);

	writel(formatter_frame, mcde->regs + frame);
	writel(pkt_size, mcde->regs + pkt);
	writel(0, mcde->regs + sync);
	/* Define the MIPI command: we want to write into display memory */
	val = MIPI_DCS_WRITE_MEMORY_CONTINUE <<
		MCDE_DSIVIDXCMDW_CMDW_CONTINUE_SHIFT;
	val |= MIPI_DCS_WRITE_MEMORY_START <<
		MCDE_DSIVIDXCMDW_CMDW_START_SHIFT;
	writel(val, mcde->regs + cmdw);

	/*
	 * FIXME: the vendor driver has some hack around this value in
	 * CMD mode with autotrig.
	 */
	writel(0, mcde->regs + delay0);
	writel(0, mcde->regs + delay1);
}