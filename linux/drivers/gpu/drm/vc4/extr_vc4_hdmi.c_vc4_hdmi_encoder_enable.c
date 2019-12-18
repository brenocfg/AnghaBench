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
struct vc4_hdmi_encoder {int limited_rgb_range; scalar_t__ hdmi_monitor; } ;
struct vc4_hdmi {int /*<<< orphan*/  hd_regset; int /*<<< orphan*/  hdmi_regset; TYPE_3__* pdev; int /*<<< orphan*/  pixel_clock; } ;
struct vc4_dev {struct vc4_hdmi* hdmi; } ;
struct drm_printer {int dummy; } ;
struct drm_encoder {struct drm_device* dev; TYPE_2__* crtc; } ;
struct drm_display_mode {int flags; int crtc_vsync_end; int crtc_vsync_start; int crtc_vdisplay; int crtc_vtotal; int clock; int hdisplay; int htotal; int hsync_end; int hsync_start; } ;
struct drm_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_1__* state; } ;
struct TYPE_4__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int DRM_MODE_FLAG_DBLCLK ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 scalar_t__ HDMI_QUANTIZATION_RANGE_LIMITED ; 
 int HDMI_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDMI_WRITE (int /*<<< orphan*/ ,int) ; 
 int HD_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HD_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VC4_HDMI_FIFO_CTL ; 
 int VC4_HDMI_FIFO_CTL_MASTER_SLAVE_N ; 
 int VC4_HDMI_FIFO_CTL_RECENTER ; 
 int VC4_HDMI_FIFO_CTL_RECENTER_DONE ; 
 int VC4_HDMI_FIFO_VALID_WRITE_MASK ; 
 int /*<<< orphan*/  VC4_HDMI_HORZA ; 
 int /*<<< orphan*/  VC4_HDMI_HORZA_HAP ; 
 int VC4_HDMI_HORZA_HPOS ; 
 int VC4_HDMI_HORZA_VPOS ; 
 int /*<<< orphan*/  VC4_HDMI_HORZB ; 
 int /*<<< orphan*/  VC4_HDMI_HORZB_HBP ; 
 int /*<<< orphan*/  VC4_HDMI_HORZB_HFP ; 
 int /*<<< orphan*/  VC4_HDMI_HORZB_HSP ; 
 int /*<<< orphan*/  VC4_HDMI_RAM_PACKET_CONFIG ; 
 int VC4_HDMI_RAM_PACKET_ENABLE ; 
 int /*<<< orphan*/  VC4_HDMI_SCHEDULER_CONTROL ; 
 int VC4_HDMI_SCHEDULER_CONTROL_HDMI_ACTIVE ; 
 int VC4_HDMI_SCHEDULER_CONTROL_IGNORE_VSYNC_PREDICTS ; 
 int VC4_HDMI_SCHEDULER_CONTROL_MANUAL_FORMAT ; 
 int VC4_HDMI_SCHEDULER_CONTROL_MODE_HDMI ; 
 int VC4_HDMI_SCHEDULER_CONTROL_VERT_ALWAYS_KEEPOUT ; 
 int /*<<< orphan*/  VC4_HDMI_SW_RESET_CONTROL ; 
 int VC4_HDMI_SW_RESET_FORMAT_DETECT ; 
 int VC4_HDMI_SW_RESET_HDMI ; 
 int /*<<< orphan*/  VC4_HDMI_TX_PHY_RESET_CTL ; 
 int /*<<< orphan*/  VC4_HDMI_VERTA0 ; 
 int /*<<< orphan*/  VC4_HDMI_VERTA1 ; 
 int /*<<< orphan*/  VC4_HDMI_VERTA_VAL ; 
 int /*<<< orphan*/  VC4_HDMI_VERTA_VFP ; 
 int /*<<< orphan*/  VC4_HDMI_VERTA_VSP ; 
 int /*<<< orphan*/  VC4_HDMI_VERTB0 ; 
 int /*<<< orphan*/  VC4_HDMI_VERTB1 ; 
 int /*<<< orphan*/  VC4_HDMI_VERTB_VBP ; 
 int /*<<< orphan*/  VC4_HDMI_VERTB_VSPO ; 
 int /*<<< orphan*/  VC4_HD_CSC_12_11 ; 
 int /*<<< orphan*/  VC4_HD_CSC_14_13 ; 
 int /*<<< orphan*/  VC4_HD_CSC_22_21 ; 
 int /*<<< orphan*/  VC4_HD_CSC_24_23 ; 
 int /*<<< orphan*/  VC4_HD_CSC_32_31 ; 
 int /*<<< orphan*/  VC4_HD_CSC_34_33 ; 
 int /*<<< orphan*/  VC4_HD_CSC_CTL ; 
 int VC4_HD_CSC_CTL_ENABLE ; 
 int /*<<< orphan*/  VC4_HD_CSC_CTL_MODE ; 
 int VC4_HD_CSC_CTL_MODE_CUSTOM ; 
 int /*<<< orphan*/  VC4_HD_CSC_CTL_ORDER ; 
 int VC4_HD_CSC_CTL_ORDER_BGR ; 
 int VC4_HD_CSC_CTL_RGB2YCC ; 
 int /*<<< orphan*/  VC4_HD_VID_CTL ; 
 int VC4_HD_VID_CTL_ENABLE ; 
 int VC4_HD_VID_CTL_FRAME_COUNTER_RESET ; 
 int VC4_HD_VID_CTL_HSYNC_LOW ; 
 int VC4_HD_VID_CTL_UNDERFLOW_ENABLE ; 
 int VC4_HD_VID_CTL_VSYNC_LOW ; 
 int VC4_SET_FIELD (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ drm_default_rgb_quant_range (struct drm_display_mode*) ; 
 struct drm_printer drm_info_printer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_print_regset32 (struct drm_printer*,int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 struct vc4_hdmi_encoder* to_vc4_hdmi_encoder (struct drm_encoder*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  vc4_hdmi_set_infoframes (struct drm_encoder*) ; 
 int wait_for (int,int) ; 

__attribute__((used)) static void vc4_hdmi_encoder_enable(struct drm_encoder *encoder)
{
	struct drm_display_mode *mode = &encoder->crtc->state->adjusted_mode;
	struct vc4_hdmi_encoder *vc4_encoder = to_vc4_hdmi_encoder(encoder);
	struct drm_device *dev = encoder->dev;
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	struct vc4_hdmi *hdmi = vc4->hdmi;
	bool debug_dump_regs = false;
	bool hsync_pos = mode->flags & DRM_MODE_FLAG_PHSYNC;
	bool vsync_pos = mode->flags & DRM_MODE_FLAG_PVSYNC;
	bool interlaced = mode->flags & DRM_MODE_FLAG_INTERLACE;
	u32 pixel_rep = (mode->flags & DRM_MODE_FLAG_DBLCLK) ? 2 : 1;
	u32 verta = (VC4_SET_FIELD(mode->crtc_vsync_end - mode->crtc_vsync_start,
				   VC4_HDMI_VERTA_VSP) |
		     VC4_SET_FIELD(mode->crtc_vsync_start - mode->crtc_vdisplay,
				   VC4_HDMI_VERTA_VFP) |
		     VC4_SET_FIELD(mode->crtc_vdisplay, VC4_HDMI_VERTA_VAL));
	u32 vertb = (VC4_SET_FIELD(0, VC4_HDMI_VERTB_VSPO) |
		     VC4_SET_FIELD(mode->crtc_vtotal - mode->crtc_vsync_end,
				   VC4_HDMI_VERTB_VBP));
	u32 vertb_even = (VC4_SET_FIELD(0, VC4_HDMI_VERTB_VSPO) |
			  VC4_SET_FIELD(mode->crtc_vtotal -
					mode->crtc_vsync_end -
					interlaced,
					VC4_HDMI_VERTB_VBP));
	u32 csc_ctl;
	int ret;

	ret = pm_runtime_get_sync(&hdmi->pdev->dev);
	if (ret < 0) {
		DRM_ERROR("Failed to retain power domain: %d\n", ret);
		return;
	}

	ret = clk_set_rate(hdmi->pixel_clock,
			   mode->clock * 1000 *
			   ((mode->flags & DRM_MODE_FLAG_DBLCLK) ? 2 : 1));
	if (ret) {
		DRM_ERROR("Failed to set pixel clock rate: %d\n", ret);
		return;
	}

	ret = clk_prepare_enable(hdmi->pixel_clock);
	if (ret) {
		DRM_ERROR("Failed to turn on pixel clock: %d\n", ret);
		return;
	}

	HDMI_WRITE(VC4_HDMI_SW_RESET_CONTROL,
		   VC4_HDMI_SW_RESET_HDMI |
		   VC4_HDMI_SW_RESET_FORMAT_DETECT);

	HDMI_WRITE(VC4_HDMI_SW_RESET_CONTROL, 0);

	/* PHY should be in reset, like
	 * vc4_hdmi_encoder_disable() does.
	 */
	HDMI_WRITE(VC4_HDMI_TX_PHY_RESET_CTL, 0xf << 16);

	HDMI_WRITE(VC4_HDMI_TX_PHY_RESET_CTL, 0);

	if (debug_dump_regs) {
		struct drm_printer p = drm_info_printer(&hdmi->pdev->dev);

		dev_info(&hdmi->pdev->dev, "HDMI regs before:\n");
		drm_print_regset32(&p, &hdmi->hdmi_regset);
		drm_print_regset32(&p, &hdmi->hd_regset);
	}

	HD_WRITE(VC4_HD_VID_CTL, 0);

	HDMI_WRITE(VC4_HDMI_SCHEDULER_CONTROL,
		   HDMI_READ(VC4_HDMI_SCHEDULER_CONTROL) |
		   VC4_HDMI_SCHEDULER_CONTROL_MANUAL_FORMAT |
		   VC4_HDMI_SCHEDULER_CONTROL_IGNORE_VSYNC_PREDICTS);

	HDMI_WRITE(VC4_HDMI_HORZA,
		   (vsync_pos ? VC4_HDMI_HORZA_VPOS : 0) |
		   (hsync_pos ? VC4_HDMI_HORZA_HPOS : 0) |
		   VC4_SET_FIELD(mode->hdisplay * pixel_rep,
				 VC4_HDMI_HORZA_HAP));

	HDMI_WRITE(VC4_HDMI_HORZB,
		   VC4_SET_FIELD((mode->htotal -
				  mode->hsync_end) * pixel_rep,
				 VC4_HDMI_HORZB_HBP) |
		   VC4_SET_FIELD((mode->hsync_end -
				  mode->hsync_start) * pixel_rep,
				 VC4_HDMI_HORZB_HSP) |
		   VC4_SET_FIELD((mode->hsync_start -
				  mode->hdisplay) * pixel_rep,
				 VC4_HDMI_HORZB_HFP));

	HDMI_WRITE(VC4_HDMI_VERTA0, verta);
	HDMI_WRITE(VC4_HDMI_VERTA1, verta);

	HDMI_WRITE(VC4_HDMI_VERTB0, vertb_even);
	HDMI_WRITE(VC4_HDMI_VERTB1, vertb);

	HD_WRITE(VC4_HD_VID_CTL,
		 (vsync_pos ? 0 : VC4_HD_VID_CTL_VSYNC_LOW) |
		 (hsync_pos ? 0 : VC4_HD_VID_CTL_HSYNC_LOW));

	csc_ctl = VC4_SET_FIELD(VC4_HD_CSC_CTL_ORDER_BGR,
				VC4_HD_CSC_CTL_ORDER);

	if (vc4_encoder->hdmi_monitor &&
	    drm_default_rgb_quant_range(mode) ==
	    HDMI_QUANTIZATION_RANGE_LIMITED) {
		/* CEA VICs other than #1 requre limited range RGB
		 * output unless overridden by an AVI infoframe.
		 * Apply a colorspace conversion to squash 0-255 down
		 * to 16-235.  The matrix here is:
		 *
		 * [ 0      0      0.8594 16]
		 * [ 0      0.8594 0      16]
		 * [ 0.8594 0      0      16]
		 * [ 0      0      0       1]
		 */
		csc_ctl |= VC4_HD_CSC_CTL_ENABLE;
		csc_ctl |= VC4_HD_CSC_CTL_RGB2YCC;
		csc_ctl |= VC4_SET_FIELD(VC4_HD_CSC_CTL_MODE_CUSTOM,
					 VC4_HD_CSC_CTL_MODE);

		HD_WRITE(VC4_HD_CSC_12_11, (0x000 << 16) | 0x000);
		HD_WRITE(VC4_HD_CSC_14_13, (0x100 << 16) | 0x6e0);
		HD_WRITE(VC4_HD_CSC_22_21, (0x6e0 << 16) | 0x000);
		HD_WRITE(VC4_HD_CSC_24_23, (0x100 << 16) | 0x000);
		HD_WRITE(VC4_HD_CSC_32_31, (0x000 << 16) | 0x6e0);
		HD_WRITE(VC4_HD_CSC_34_33, (0x100 << 16) | 0x000);
		vc4_encoder->limited_rgb_range = true;
	} else {
		vc4_encoder->limited_rgb_range = false;
	}

	/* The RGB order applies even when CSC is disabled. */
	HD_WRITE(VC4_HD_CSC_CTL, csc_ctl);

	HDMI_WRITE(VC4_HDMI_FIFO_CTL, VC4_HDMI_FIFO_CTL_MASTER_SLAVE_N);

	if (debug_dump_regs) {
		struct drm_printer p = drm_info_printer(&hdmi->pdev->dev);

		dev_info(&hdmi->pdev->dev, "HDMI regs after:\n");
		drm_print_regset32(&p, &hdmi->hdmi_regset);
		drm_print_regset32(&p, &hdmi->hd_regset);
	}

	HD_WRITE(VC4_HD_VID_CTL,
		 HD_READ(VC4_HD_VID_CTL) |
		 VC4_HD_VID_CTL_ENABLE |
		 VC4_HD_VID_CTL_UNDERFLOW_ENABLE |
		 VC4_HD_VID_CTL_FRAME_COUNTER_RESET);

	if (vc4_encoder->hdmi_monitor) {
		HDMI_WRITE(VC4_HDMI_SCHEDULER_CONTROL,
			   HDMI_READ(VC4_HDMI_SCHEDULER_CONTROL) |
			   VC4_HDMI_SCHEDULER_CONTROL_MODE_HDMI);

		ret = wait_for(HDMI_READ(VC4_HDMI_SCHEDULER_CONTROL) &
			       VC4_HDMI_SCHEDULER_CONTROL_HDMI_ACTIVE, 1000);
		WARN_ONCE(ret, "Timeout waiting for "
			  "VC4_HDMI_SCHEDULER_CONTROL_HDMI_ACTIVE\n");
	} else {
		HDMI_WRITE(VC4_HDMI_RAM_PACKET_CONFIG,
			   HDMI_READ(VC4_HDMI_RAM_PACKET_CONFIG) &
			   ~(VC4_HDMI_RAM_PACKET_ENABLE));
		HDMI_WRITE(VC4_HDMI_SCHEDULER_CONTROL,
			   HDMI_READ(VC4_HDMI_SCHEDULER_CONTROL) &
			   ~VC4_HDMI_SCHEDULER_CONTROL_MODE_HDMI);

		ret = wait_for(!(HDMI_READ(VC4_HDMI_SCHEDULER_CONTROL) &
				 VC4_HDMI_SCHEDULER_CONTROL_HDMI_ACTIVE), 1000);
		WARN_ONCE(ret, "Timeout waiting for "
			  "!VC4_HDMI_SCHEDULER_CONTROL_HDMI_ACTIVE\n");
	}

	if (vc4_encoder->hdmi_monitor) {
		u32 drift;

		WARN_ON(!(HDMI_READ(VC4_HDMI_SCHEDULER_CONTROL) &
			  VC4_HDMI_SCHEDULER_CONTROL_HDMI_ACTIVE));
		HDMI_WRITE(VC4_HDMI_SCHEDULER_CONTROL,
			   HDMI_READ(VC4_HDMI_SCHEDULER_CONTROL) |
			   VC4_HDMI_SCHEDULER_CONTROL_VERT_ALWAYS_KEEPOUT);

		HDMI_WRITE(VC4_HDMI_RAM_PACKET_CONFIG,
			   VC4_HDMI_RAM_PACKET_ENABLE);

		vc4_hdmi_set_infoframes(encoder);

		drift = HDMI_READ(VC4_HDMI_FIFO_CTL);
		drift &= VC4_HDMI_FIFO_VALID_WRITE_MASK;

		HDMI_WRITE(VC4_HDMI_FIFO_CTL,
			   drift & ~VC4_HDMI_FIFO_CTL_RECENTER);
		HDMI_WRITE(VC4_HDMI_FIFO_CTL,
			   drift | VC4_HDMI_FIFO_CTL_RECENTER);
		usleep_range(1000, 1100);
		HDMI_WRITE(VC4_HDMI_FIFO_CTL,
			   drift & ~VC4_HDMI_FIFO_CTL_RECENTER);
		HDMI_WRITE(VC4_HDMI_FIFO_CTL,
			   drift | VC4_HDMI_FIFO_CTL_RECENTER);

		ret = wait_for(HDMI_READ(VC4_HDMI_FIFO_CTL) &
			       VC4_HDMI_FIFO_CTL_RECENTER_DONE, 1);
		WARN_ONCE(ret, "Timeout waiting for "
			  "VC4_HDMI_FIFO_CTL_RECENTER_DONE");
	}
}