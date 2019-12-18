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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct mcde_dsi {int hs_freq; scalar_t__ regs; TYPE_1__* mdsi; int /*<<< orphan*/  dev; } ;
struct drm_display_mode {int vdisplay; int vsync_start; int vsync_end; int vtotal; int hsync_start; int hdisplay; int htotal; int hsync_end; int clock; } ;
struct TYPE_2__ {int format; int mode_flags; int lanes; } ;

/* Variables and functions */
 scalar_t__ DSI_CMD_MODE_CTL ; 
 int DSI_CMD_MODE_CTL_IF1_LP_EN ; 
 scalar_t__ DSI_MCTL_MAIN_DATA_CTL ; 
 int DSI_MCTL_MAIN_DATA_CTL_IF1_MODE ; 
 int DSI_MCTL_MAIN_DATA_CTL_VID_EN ; 
 scalar_t__ DSI_VID_BLKSIZE1 ; 
 int DSI_VID_BLKSIZE1_BLKEOL_PCK_SHIFT ; 
 int DSI_VID_BLKSIZE1_BLKLINE_EVENT_PCK_SHIFT ; 
 scalar_t__ DSI_VID_BLKSIZE2 ; 
 int DSI_VID_BLKSIZE2_BLKLINE_PULSE_PCK_SHIFT ; 
 scalar_t__ DSI_VID_DPHY_TIME ; 
 int DSI_VID_DPHY_TIME_REG_LINE_DURATION_SHIFT ; 
 int DSI_VID_DPHY_TIME_REG_WAKEUP_TIME_SHIFT ; 
 scalar_t__ DSI_VID_HSIZE1 ; 
 int DSI_VID_HSIZE1_HBP_LENGTH_SHIFT ; 
 int DSI_VID_HSIZE1_HFP_LENGTH_SHIFT ; 
 int DSI_VID_HSIZE1_HSA_LENGTH_SHIFT ; 
 scalar_t__ DSI_VID_HSIZE2 ; 
 scalar_t__ DSI_VID_MAIN_CTL ; 
 int DSI_VID_MAIN_CTL_BURST_MODE ; 
 int DSI_VID_MAIN_CTL_HEADER_SHIFT ; 
 int DSI_VID_MAIN_CTL_RECOVERY_MODE_SHIFT ; 
 int DSI_VID_MAIN_CTL_REG_BLKEOL_MODE_LP_0 ; 
 int DSI_VID_MAIN_CTL_REG_BLKLINE_MODE_LP_0 ; 
 int DSI_VID_MAIN_CTL_SYNC_PULSE_ACTIVE ; 
 int DSI_VID_MAIN_CTL_SYNC_PULSE_HORIZONTAL ; 
 int DSI_VID_MAIN_CTL_VID_PIXEL_MODE_16BITS ; 
 int DSI_VID_MAIN_CTL_VID_PIXEL_MODE_18BITS ; 
 int DSI_VID_MAIN_CTL_VID_PIXEL_MODE_18BITS_LOOSE ; 
 int DSI_VID_MAIN_CTL_VID_PIXEL_MODE_24BITS ; 
 scalar_t__ DSI_VID_MODE_STS_CTL ; 
 int DSI_VID_MODE_STS_CTL_ERR_MISSING_DATA ; 
 int DSI_VID_MODE_STS_CTL_ERR_MISSING_VSYNC ; 
 scalar_t__ DSI_VID_PCK_TIME ; 
 scalar_t__ DSI_VID_VCA_SETTING1 ; 
 scalar_t__ DSI_VID_VCA_SETTING2 ; 
 int DSI_VID_VCA_SETTING2_EXACT_BURST_LIMIT_SHIFT ; 
 scalar_t__ DSI_VID_VSIZE ; 
 int DSI_VID_VSIZE_VACT_LENGTH_SHIFT ; 
 int DSI_VID_VSIZE_VBP_LENGTH_SHIFT ; 
 int DSI_VID_VSIZE_VFP_LENGTH_SHIFT ; 
 int DSI_VID_VSIZE_VSA_LENGTH_SHIFT ; 
#define  MIPI_DSI_FMT_RGB565 131 
#define  MIPI_DSI_FMT_RGB666 130 
#define  MIPI_DSI_FMT_RGB666_PACKED 129 
#define  MIPI_DSI_FMT_RGB888 128 
 int MIPI_DSI_MODE_VIDEO_BURST ; 
 int MIPI_DSI_MODE_VIDEO_SYNC_PULSE ; 
 int MIPI_DSI_PACKED_PIXEL_STREAM_16 ; 
 int MIPI_DSI_PACKED_PIXEL_STREAM_18 ; 
 int MIPI_DSI_PACKED_PIXEL_STREAM_24 ; 
 int MIPI_DSI_PIXEL_STREAM_3BYTE_18 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int mipi_dsi_pixel_format_to_bpp (int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mcde_dsi_setup_video_mode(struct mcde_dsi *d,
				      const struct drm_display_mode *mode)
{
	u8 bpp = mipi_dsi_pixel_format_to_bpp(d->mdsi->format);
	u64 bpl;
	u32 hfp;
	u32 hbp;
	u32 hsa;
	u32 blkline_pck, line_duration;
	u32 blkeol_pck, blkeol_duration;
	u32 val;

	val = 0;
	if (d->mdsi->mode_flags & MIPI_DSI_MODE_VIDEO_BURST)
		val |= DSI_VID_MAIN_CTL_BURST_MODE;
	if (d->mdsi->mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE) {
		val |= DSI_VID_MAIN_CTL_SYNC_PULSE_ACTIVE;
		val |= DSI_VID_MAIN_CTL_SYNC_PULSE_HORIZONTAL;
	}
	/* RGB header and pixel mode */
	switch (d->mdsi->format) {
	case MIPI_DSI_FMT_RGB565:
		val |= MIPI_DSI_PACKED_PIXEL_STREAM_16 <<
			DSI_VID_MAIN_CTL_HEADER_SHIFT;
		val |= DSI_VID_MAIN_CTL_VID_PIXEL_MODE_16BITS;
		break;
	case MIPI_DSI_FMT_RGB666_PACKED:
		val |= MIPI_DSI_PACKED_PIXEL_STREAM_18 <<
			DSI_VID_MAIN_CTL_HEADER_SHIFT;
		val |= DSI_VID_MAIN_CTL_VID_PIXEL_MODE_18BITS;
		break;
	case MIPI_DSI_FMT_RGB666:
		val |= MIPI_DSI_PIXEL_STREAM_3BYTE_18
			<< DSI_VID_MAIN_CTL_HEADER_SHIFT;
		val |= DSI_VID_MAIN_CTL_VID_PIXEL_MODE_18BITS_LOOSE;
		break;
	case MIPI_DSI_FMT_RGB888:
		val |= MIPI_DSI_PACKED_PIXEL_STREAM_24 <<
			DSI_VID_MAIN_CTL_HEADER_SHIFT;
		val |= DSI_VID_MAIN_CTL_VID_PIXEL_MODE_24BITS;
		break;
	default:
		dev_err(d->dev, "unknown pixel mode\n");
		return;
	}

	/* TODO: TVG could be enabled here */

	/* Send blanking packet */
	val |= DSI_VID_MAIN_CTL_REG_BLKLINE_MODE_LP_0;
	/* Send EOL packet */
	val |= DSI_VID_MAIN_CTL_REG_BLKEOL_MODE_LP_0;
	/* Recovery mode 1 */
	val |= 1 << DSI_VID_MAIN_CTL_RECOVERY_MODE_SHIFT;
	/* All other fields zero */
	writel(val, d->regs + DSI_VID_MAIN_CTL);

	/* Vertical frame parameters are pretty straight-forward */
	val = mode->vdisplay << DSI_VID_VSIZE_VSA_LENGTH_SHIFT;
	/* vertical front porch */
	val |= (mode->vsync_start - mode->vdisplay)
		<< DSI_VID_VSIZE_VFP_LENGTH_SHIFT;
	/* vertical sync active */
	val |= (mode->vsync_end - mode->vsync_start)
		<< DSI_VID_VSIZE_VACT_LENGTH_SHIFT;
	/* vertical back porch */
	val |= (mode->vtotal - mode->vsync_end)
		<< DSI_VID_VSIZE_VBP_LENGTH_SHIFT;
	writel(val, d->regs + DSI_VID_VSIZE);

	/*
	 * Horizontal frame parameters:
	 * horizontal resolution is given in pixels and must be re-calculated
	 * into bytes since this is what the hardware expects.
	 *
	 * 6 + 2 is HFP header + checksum
	 */
	hfp = (mode->hsync_start - mode->hdisplay) * bpp - 6 - 2;
	if (d->mdsi->mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE) {
		/*
		 * 6 is HBP header + checksum
		 * 4 is RGB header + checksum
		 */
		hbp = (mode->htotal - mode->hsync_end) * bpp - 4 - 6;
		/*
		 * 6 is HBP header + checksum
		 * 4 is HSW packet bytes
		 * 4 is RGB header + checksum
		 */
		hsa = (mode->hsync_end - mode->hsync_start) * bpp - 4 - 4 - 6;
	} else {
		/*
		 * HBP includes both back porch and sync
		 * 6 is HBP header + checksum
		 * 4 is HSW packet bytes
		 * 4 is RGB header + checksum
		 */
		hbp = (mode->htotal - mode->hsync_start) * bpp - 4 - 4 - 6;
		/* HSA is not considered in this mode and set to 0 */
		hsa = 0;
	}
	dev_dbg(d->dev, "hfp: %u, hbp: %u, hsa: %u\n",
		hfp, hbp, hsa);

	/* Frame parameters: horizontal sync active */
	val = hsa << DSI_VID_HSIZE1_HSA_LENGTH_SHIFT;
	/* horizontal back porch */
	val |= hbp << DSI_VID_HSIZE1_HBP_LENGTH_SHIFT;
	/* horizontal front porch */
	val |= hfp << DSI_VID_HSIZE1_HFP_LENGTH_SHIFT;
	writel(val, d->regs + DSI_VID_HSIZE1);

	/* RGB data length (bytes on one scanline) */
	val = mode->hdisplay * (bpp / 8);
	writel(val, d->regs + DSI_VID_HSIZE2);

	/* TODO: further adjustments for TVG mode here */

	/*
	 * EOL packet length from bits per line calculations: pixel clock
	 * is given in kHz, calculate the time between two pixels in
	 * picoseconds.
	 */
	bpl = mode->clock * mode->htotal;
	bpl *= (d->hs_freq / 8);
	do_div(bpl, 1000000); /* microseconds */
	do_div(bpl, 1000000); /* seconds */
	bpl *= d->mdsi->lanes;
	dev_dbg(d->dev, "calculated bytes per line: %llu\n", bpl);
	/*
	 * 6 is header + checksum, header = 4 bytes, checksum = 2 bytes
	 * 4 is short packet for vsync/hsync
	 */
	if (d->mdsi->mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE) {
		/* Fixme: isn't the hsync width in pixels? */
		blkline_pck = bpl - (mode->hsync_end - mode->hsync_start) - 6;
		val = blkline_pck << DSI_VID_BLKSIZE2_BLKLINE_PULSE_PCK_SHIFT;
		writel(val, d->regs + DSI_VID_BLKSIZE2);
	} else {
		blkline_pck = bpl - 4 - 6;
		val = blkline_pck << DSI_VID_BLKSIZE1_BLKLINE_EVENT_PCK_SHIFT;
		writel(val, d->regs + DSI_VID_BLKSIZE1);
	}

	line_duration = (blkline_pck + 6) / d->mdsi->lanes;
	dev_dbg(d->dev, "line duration %u\n", line_duration);
	val = line_duration << DSI_VID_DPHY_TIME_REG_LINE_DURATION_SHIFT;
	/*
	 * This is the time to perform LP->HS on D-PHY
	 * FIXME: nowhere to get this from: DT property on the DSI?
	 */
	val |= 0 << DSI_VID_DPHY_TIME_REG_WAKEUP_TIME_SHIFT;
	writel(val, d->regs + DSI_VID_DPHY_TIME);

	/* Calculate block end of line */
	blkeol_pck = bpl - mode->hdisplay * bpp - 6;
	blkeol_duration = (blkeol_pck + 6) / d->mdsi->lanes;
	dev_dbg(d->dev, "blkeol pck: %u, duration: %u\n",
		 blkeol_pck, blkeol_duration);

	if (d->mdsi->mode_flags & MIPI_DSI_MODE_VIDEO_BURST) {
		/* Set up EOL clock for burst mode */
		val = readl(d->regs + DSI_VID_BLKSIZE1);
		val |= blkeol_pck << DSI_VID_BLKSIZE1_BLKEOL_PCK_SHIFT;
		writel(val, d->regs + DSI_VID_BLKSIZE1);
		writel(blkeol_pck, d->regs + DSI_VID_VCA_SETTING2);

		writel(blkeol_duration, d->regs + DSI_VID_PCK_TIME);
		writel(blkeol_duration - 6, d->regs + DSI_VID_VCA_SETTING1);
	}

	/* Maximum line limit */
	val = readl(d->regs + DSI_VID_VCA_SETTING2);
	val |= blkline_pck <<
		DSI_VID_VCA_SETTING2_EXACT_BURST_LIMIT_SHIFT;
	writel(val, d->regs + DSI_VID_VCA_SETTING2);

	/* Put IF1 into video mode */
	val = readl(d->regs + DSI_MCTL_MAIN_DATA_CTL);
	val |= DSI_MCTL_MAIN_DATA_CTL_IF1_MODE;
	writel(val, d->regs + DSI_MCTL_MAIN_DATA_CTL);

	/* Disable command mode on IF1 */
	val = readl(d->regs + DSI_CMD_MODE_CTL);
	val &= ~DSI_CMD_MODE_CTL_IF1_LP_EN;
	writel(val, d->regs + DSI_CMD_MODE_CTL);

	/* Enable some error interrupts */
	val = readl(d->regs + DSI_VID_MODE_STS_CTL);
	val |= DSI_VID_MODE_STS_CTL_ERR_MISSING_VSYNC;
	val |= DSI_VID_MODE_STS_CTL_ERR_MISSING_DATA;
	writel(val, d->regs + DSI_VID_MODE_STS_CTL);

	/* Enable video mode */
	val = readl(d->regs + DSI_MCTL_MAIN_DATA_CTL);
	val |= DSI_MCTL_MAIN_DATA_CTL_VID_EN;
	writel(val, d->regs + DSI_MCTL_MAIN_DATA_CTL);
}