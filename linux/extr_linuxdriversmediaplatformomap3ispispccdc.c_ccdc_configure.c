#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_13__ {int code; } ;
struct v4l2_subdev_format {TYPE_4__ format; int /*<<< orphan*/  which; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_rect {int left; int width; int top; int height; } ;
struct v4l2_mbus_framefmt {int code; int height; scalar_t__ field; } ;
struct media_pad {int /*<<< orphan*/  index; int /*<<< orphan*/  entity; } ;
struct isp_parallel_cfg {int bt656; } ;
struct isp_format_info {unsigned int width; scalar_t__ code; } ;
struct isp_device {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  req_lock; TYPE_8__* request; int /*<<< orphan*/  table_work; int /*<<< orphan*/  free_queue; TYPE_8__* active; } ;
struct TYPE_14__ {int /*<<< orphan*/  bpl_value; } ;
struct TYPE_11__ {int /*<<< orphan*/  entity; } ;
struct isp_ccdc_device {int bt656; scalar_t__ input; int output; TYPE_1__ lsc; struct v4l2_mbus_framefmt* formats; TYPE_5__ video_out; struct v4l2_rect crop; TYPE_2__ subdev; int /*<<< orphan*/ * pads; scalar_t__ fields; } ;
struct TYPE_17__ {int /*<<< orphan*/  list; } ;
struct TYPE_16__ {struct v4l2_subdev* external; } ;
struct TYPE_12__ {struct isp_parallel_cfg parallel; } ;
struct TYPE_15__ {TYPE_3__ bus; } ;

/* Variables and functions */
 scalar_t__ CCDC_INPUT_PARALLEL ; 
 int CCDC_OUTPUT_MEMORY ; 
 int CCDC_OUTPUT_RESIZER ; 
 size_t CCDC_PAD_SINK ; 
 size_t CCDC_PAD_SOURCE_OF ; 
 int /*<<< orphan*/  ISPCCDC_CFG ; 
 int /*<<< orphan*/  ISPCCDC_CFG_BSWD ; 
 int /*<<< orphan*/  ISPCCDC_HORZ_INFO ; 
 unsigned int ISPCCDC_HORZ_INFO_NPH_SHIFT ; 
 unsigned int ISPCCDC_HORZ_INFO_SPH_SHIFT ; 
 int /*<<< orphan*/  ISPCCDC_SYN_MODE ; 
 int ISPCCDC_SYN_MODE_FLDMODE ; 
 int ISPCCDC_SYN_MODE_PACK8 ; 
 int ISPCCDC_SYN_MODE_SDR2RSZ ; 
 int ISPCCDC_SYN_MODE_VP2SDR ; 
 int ISPCCDC_SYN_MODE_WEN ; 
 int /*<<< orphan*/  ISPCCDC_VDINT ; 
 int ISPCCDC_VDINT_0_SHIFT ; 
 int ISPCCDC_VDINT_1_SHIFT ; 
 int /*<<< orphan*/  ISPCCDC_VERT_LINES ; 
 int ISPCCDC_VERT_LINES_NLV_SHIFT ; 
 int /*<<< orphan*/  ISPCCDC_VERT_START ; 
 int ISPCCDC_VERT_START_SLV0_SHIFT ; 
 int ISPCCDC_VERT_START_SLV1_SHIFT ; 
 unsigned int ISPCTRL_PAR_BRIDGE_BENDIAN ; 
 unsigned int ISPCTRL_PAR_BRIDGE_DISABLE ; 
 unsigned int ISPCTRL_PAR_BRIDGE_LENDIAN ; 
#define  MEDIA_BUS_FMT_SBGGR10_1X10 133 
#define  MEDIA_BUS_FMT_SBGGR12_1X12 132 
#define  MEDIA_BUS_FMT_SGBRG10_1X10 131 
#define  MEDIA_BUS_FMT_SGBRG12_1X12 130 
#define  MEDIA_BUS_FMT_SRGGB10_1X10 129 
#define  MEDIA_BUS_FMT_SRGGB12_1X12 128 
 scalar_t__ MEDIA_BUS_FMT_UYVY8_2X8 ; 
 int MEDIA_BUS_FMT_YUYV8_1X16 ; 
 scalar_t__ MEDIA_BUS_FMT_YUYV8_2X8 ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_CCDC ; 
 scalar_t__ V4L2_FIELD_ALTERNATE ; 
 scalar_t__ V4L2_FIELD_INTERLACED_BT ; 
 scalar_t__ V4L2_FIELD_INTERLACED_TB ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  WARN_ON (TYPE_8__*) ; 
 scalar_t__ __ccdc_lsc_configure (struct isp_ccdc_device*,TYPE_8__*) ; 
 int /*<<< orphan*/  ccdc_apply_controls (struct isp_ccdc_device*) ; 
 int /*<<< orphan*/  ccdc_config_imgattr (struct isp_ccdc_device*,int) ; 
 int /*<<< orphan*/  ccdc_config_outlineoffset (struct isp_ccdc_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ccdc_config_sync_if (struct isp_ccdc_device*,struct isp_parallel_cfg*,unsigned int) ; 
 int /*<<< orphan*/  ccdc_config_vp (struct isp_ccdc_device*) ; 
 int ccdc_sbggr_pattern ; 
 int ccdc_sgbrg_pattern ; 
 int ccdc_sgrbg_pattern ; 
 int ccdc_srggb_pattern ; 
 int /*<<< orphan*/  get_fmt ; 
 int /*<<< orphan*/  isp_reg_clr (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int isp_reg_readl (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_reg_set (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct media_pad* media_entity_remote_pad (int /*<<< orphan*/ *) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap3isp_configure_bridge (struct isp_device*,scalar_t__,struct isp_parallel_cfg*,unsigned int,unsigned int) ; 
 struct isp_format_info* omap3isp_video_format_info (int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct isp_device* to_isp_device (struct isp_ccdc_device*) ; 
 TYPE_7__* to_isp_pipeline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_subdev_call (struct v4l2_subdev*,struct media_pad*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 
 TYPE_6__* v4l2_subdev_to_bus_cfg (struct v4l2_subdev*) ; 

__attribute__((used)) static void ccdc_configure(struct isp_ccdc_device *ccdc)
{
	struct isp_device *isp = to_isp_device(ccdc);
	struct isp_parallel_cfg *parcfg = NULL;
	struct v4l2_subdev *sensor;
	struct v4l2_mbus_framefmt *format;
	const struct v4l2_rect *crop;
	const struct isp_format_info *fmt_info;
	struct v4l2_subdev_format fmt_src;
	unsigned int depth_out;
	unsigned int depth_in = 0;
	struct media_pad *pad;
	unsigned long flags;
	unsigned int bridge;
	unsigned int shift;
	unsigned int nph;
	unsigned int sph;
	u32 syn_mode;
	u32 ccdc_pattern;

	ccdc->bt656 = false;
	ccdc->fields = 0;

	pad = media_entity_remote_pad(&ccdc->pads[CCDC_PAD_SINK]);
	sensor = media_entity_to_v4l2_subdev(pad->entity);
	if (ccdc->input == CCDC_INPUT_PARALLEL) {
		struct v4l2_subdev *sd =
			to_isp_pipeline(&ccdc->subdev.entity)->external;

		parcfg = &v4l2_subdev_to_bus_cfg(sd)->bus.parallel;
		ccdc->bt656 = parcfg->bt656;
	}

	/* CCDC_PAD_SINK */
	format = &ccdc->formats[CCDC_PAD_SINK];

	/* Compute the lane shifter shift value and enable the bridge when the
	 * input format is a non-BT.656 YUV variant.
	 */
	fmt_src.pad = pad->index;
	fmt_src.which = V4L2_SUBDEV_FORMAT_ACTIVE;
	if (!v4l2_subdev_call(sensor, pad, get_fmt, NULL, &fmt_src)) {
		fmt_info = omap3isp_video_format_info(fmt_src.format.code);
		depth_in = fmt_info->width;
	}

	fmt_info = omap3isp_video_format_info(format->code);
	depth_out = fmt_info->width;
	shift = depth_in - depth_out;

	if (ccdc->bt656)
		bridge = ISPCTRL_PAR_BRIDGE_DISABLE;
	else if (fmt_info->code == MEDIA_BUS_FMT_YUYV8_2X8)
		bridge = ISPCTRL_PAR_BRIDGE_LENDIAN;
	else if (fmt_info->code == MEDIA_BUS_FMT_UYVY8_2X8)
		bridge = ISPCTRL_PAR_BRIDGE_BENDIAN;
	else
		bridge = ISPCTRL_PAR_BRIDGE_DISABLE;

	omap3isp_configure_bridge(isp, ccdc->input, parcfg, shift, bridge);

	/* Configure the sync interface. */
	ccdc_config_sync_if(ccdc, parcfg, depth_out);

	syn_mode = isp_reg_readl(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_SYN_MODE);

	/* Use the raw, unprocessed data when writing to memory. The H3A and
	 * histogram modules are still fed with lens shading corrected data.
	 */
	syn_mode &= ~ISPCCDC_SYN_MODE_VP2SDR;

	if (ccdc->output & CCDC_OUTPUT_MEMORY)
		syn_mode |= ISPCCDC_SYN_MODE_WEN;
	else
		syn_mode &= ~ISPCCDC_SYN_MODE_WEN;

	if (ccdc->output & CCDC_OUTPUT_RESIZER)
		syn_mode |= ISPCCDC_SYN_MODE_SDR2RSZ;
	else
		syn_mode &= ~ISPCCDC_SYN_MODE_SDR2RSZ;

	/* Mosaic filter */
	switch (format->code) {
	case MEDIA_BUS_FMT_SRGGB10_1X10:
	case MEDIA_BUS_FMT_SRGGB12_1X12:
		ccdc_pattern = ccdc_srggb_pattern;
		break;
	case MEDIA_BUS_FMT_SBGGR10_1X10:
	case MEDIA_BUS_FMT_SBGGR12_1X12:
		ccdc_pattern = ccdc_sbggr_pattern;
		break;
	case MEDIA_BUS_FMT_SGBRG10_1X10:
	case MEDIA_BUS_FMT_SGBRG12_1X12:
		ccdc_pattern = ccdc_sgbrg_pattern;
		break;
	default:
		/* Use GRBG */
		ccdc_pattern = ccdc_sgrbg_pattern;
		break;
	}
	ccdc_config_imgattr(ccdc, ccdc_pattern);

	/* Generate VD0 on the last line of the image and VD1 on the
	 * 2/3 height line.
	 */
	isp_reg_writel(isp, ((format->height - 2) << ISPCCDC_VDINT_0_SHIFT) |
		       ((format->height * 2 / 3) << ISPCCDC_VDINT_1_SHIFT),
		       OMAP3_ISP_IOMEM_CCDC, ISPCCDC_VDINT);

	/* CCDC_PAD_SOURCE_OF */
	format = &ccdc->formats[CCDC_PAD_SOURCE_OF];
	crop = &ccdc->crop;

	/* The horizontal coordinates are expressed in pixel clock cycles. We
	 * need two cycles per pixel in BT.656 mode, and one cycle per pixel in
	 * SYNC mode regardless of the format as the bridge is enabled for YUV
	 * formats in that case.
	 */
	if (ccdc->bt656) {
		sph = crop->left * 2;
		nph = crop->width * 2 - 1;
	} else {
		sph = crop->left;
		nph = crop->width - 1;
	}

	isp_reg_writel(isp, (sph << ISPCCDC_HORZ_INFO_SPH_SHIFT) |
		       (nph << ISPCCDC_HORZ_INFO_NPH_SHIFT),
		       OMAP3_ISP_IOMEM_CCDC, ISPCCDC_HORZ_INFO);
	isp_reg_writel(isp, (crop->top << ISPCCDC_VERT_START_SLV0_SHIFT) |
		       (crop->top << ISPCCDC_VERT_START_SLV1_SHIFT),
		       OMAP3_ISP_IOMEM_CCDC, ISPCCDC_VERT_START);
	isp_reg_writel(isp, (crop->height - 1)
			<< ISPCCDC_VERT_LINES_NLV_SHIFT,
		       OMAP3_ISP_IOMEM_CCDC, ISPCCDC_VERT_LINES);

	ccdc_config_outlineoffset(ccdc, ccdc->video_out.bpl_value,
				  format->field);

	/* When interleaving fields enable processing of the field input signal.
	 * This will cause the line output control module to apply the field
	 * offset to field 1.
	 */
	if (ccdc->formats[CCDC_PAD_SINK].field == V4L2_FIELD_ALTERNATE &&
	    (format->field == V4L2_FIELD_INTERLACED_TB ||
	     format->field == V4L2_FIELD_INTERLACED_BT))
		syn_mode |= ISPCCDC_SYN_MODE_FLDMODE;

	/* The CCDC outputs data in UYVY order by default. Swap bytes to get
	 * YUYV.
	 */
	if (format->code == MEDIA_BUS_FMT_YUYV8_1X16)
		isp_reg_set(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_CFG,
			    ISPCCDC_CFG_BSWD);
	else
		isp_reg_clr(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_CFG,
			    ISPCCDC_CFG_BSWD);

	/* Use PACK8 mode for 1byte per pixel formats. Check for BT.656 mode
	 * explicitly as the driver reports 1X16 instead of 2X8 at the OF pad
	 * for simplicity.
	 */
	if (omap3isp_video_format_info(format->code)->width <= 8 || ccdc->bt656)
		syn_mode |= ISPCCDC_SYN_MODE_PACK8;
	else
		syn_mode &= ~ISPCCDC_SYN_MODE_PACK8;

	isp_reg_writel(isp, syn_mode, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_SYN_MODE);

	/* CCDC_PAD_SOURCE_VP */
	ccdc_config_vp(ccdc);

	/* Lens shading correction. */
	spin_lock_irqsave(&ccdc->lsc.req_lock, flags);
	if (ccdc->lsc.request == NULL)
		goto unlock;

	WARN_ON(ccdc->lsc.active);

	/* Get last good LSC configuration. If it is not supported for
	 * the current active resolution discard it.
	 */
	if (ccdc->lsc.active == NULL &&
	    __ccdc_lsc_configure(ccdc, ccdc->lsc.request) == 0) {
		ccdc->lsc.active = ccdc->lsc.request;
	} else {
		list_add_tail(&ccdc->lsc.request->list, &ccdc->lsc.free_queue);
		schedule_work(&ccdc->lsc.table_work);
	}

	ccdc->lsc.request = NULL;

unlock:
	spin_unlock_irqrestore(&ccdc->lsc.req_lock, flags);

	ccdc_apply_controls(ccdc);
}