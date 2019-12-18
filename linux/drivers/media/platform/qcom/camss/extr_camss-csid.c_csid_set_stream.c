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
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int code; int width; int height; } ;
struct csid_testgen_config {int payload_mode; scalar_t__ enabled; } ;
struct csid_phy_config {int lane_cnt; int lane_assign; int csiphy_id; } ;
struct csid_format {int bpp; int spp; int data_type; int decode_format; } ;
struct csid_device {scalar_t__ base; struct v4l2_mbus_framefmt* fmt; TYPE_1__* camss; struct csid_phy_config phy; int /*<<< orphan*/  nformats; int /*<<< orphan*/  formats; int /*<<< orphan*/ * pads; int /*<<< orphan*/  ctrls; struct csid_testgen_config testgen; } ;
typedef  enum camss_version { ____Placeholder_camss_version } camss_version ;
struct TYPE_2__ {int version; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CAMSS_8x96 ; 
 scalar_t__ CAMSS_CSID_CID_LUT_VC_n (int,int) ; 
 scalar_t__ CAMSS_CSID_CID_n_CFG (int,int) ; 
 int CAMSS_CSID_CID_n_CFG_DECODE_FORMAT_SHIFT ; 
 int CAMSS_CSID_CID_n_CFG_ISPIF_EN ; 
 int CAMSS_CSID_CID_n_CFG_PLAIN_ALIGNMENT_LSB ; 
 int CAMSS_CSID_CID_n_CFG_PLAIN_FORMAT_16 ; 
 int CAMSS_CSID_CID_n_CFG_RDI_EN ; 
 int CAMSS_CSID_CID_n_CFG_RDI_MODE_PLAIN_PACKING ; 
 int CAMSS_CSID_CID_n_CFG_RDI_MODE_RAW_DUMP ; 
 scalar_t__ CAMSS_CSID_CORE_CTRL_0 ; 
 scalar_t__ CAMSS_CSID_CORE_CTRL_1 ; 
 scalar_t__ CAMSS_CSID_TG_CTRL (int) ; 
 int CAMSS_CSID_TG_CTRL_DISABLE ; 
 int CAMSS_CSID_TG_CTRL_ENABLE ; 
 scalar_t__ CAMSS_CSID_TG_DT_n_CGG_0 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ CAMSS_CSID_TG_DT_n_CGG_1 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ CAMSS_CSID_TG_DT_n_CGG_2 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ CAMSS_CSID_TG_VC_CFG (int) ; 
 int CAMSS_CSID_TG_VC_CFG_H_BLANKING ; 
 int CAMSS_CSID_TG_VC_CFG_V_BLANKING ; 
 int ENOLINK ; 
 int MEDIA_BUS_FMT_SBGGR10_1X10 ; 
 int MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE ; 
 int MEDIA_BUS_FMT_Y10_1X10 ; 
 int MEDIA_BUS_FMT_Y10_2X8_PADHI_LE ; 
 size_t MSM_CSID_PAD_SINK ; 
 size_t MSM_CSID_PAD_SRC ; 
 struct csid_format* csid_get_fmt_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  media_entity_remote_pad (int /*<<< orphan*/ *) ; 
 int readl_relaxed (scalar_t__) ; 
 int v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 
 struct csid_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int csid_set_stream(struct v4l2_subdev *sd, int enable)
{
	struct csid_device *csid = v4l2_get_subdevdata(sd);
	struct csid_testgen_config *tg = &csid->testgen;
	enum camss_version ver = csid->camss->version;
	u32 val;

	if (enable) {
		u8 vc = 0; /* Virtual Channel 0 */
		u8 cid = vc * 4; /* id of Virtual Channel and Data Type set */
		u8 dt, dt_shift, df;
		int ret;

		ret = v4l2_ctrl_handler_setup(&csid->ctrls);
		if (ret < 0) {
			dev_err(csid->camss->dev,
				"could not sync v4l2 controls: %d\n", ret);
			return ret;
		}

		if (!tg->enabled &&
		    !media_entity_remote_pad(&csid->pads[MSM_CSID_PAD_SINK]))
			return -ENOLINK;

		if (tg->enabled) {
			/* Config Test Generator */
			struct v4l2_mbus_framefmt *f =
					&csid->fmt[MSM_CSID_PAD_SRC];
			const struct csid_format *format = csid_get_fmt_entry(
					csid->formats, csid->nformats, f->code);
			u32 num_bytes_per_line =
				f->width * format->bpp * format->spp / 8;
			u32 num_lines = f->height;

			/* 31:24 V blank, 23:13 H blank, 3:2 num of active DT */
			/* 1:0 VC */
			val = ((CAMSS_CSID_TG_VC_CFG_V_BLANKING & 0xff) << 24) |
			      ((CAMSS_CSID_TG_VC_CFG_H_BLANKING & 0x7ff) << 13);
			writel_relaxed(val, csid->base +
				       CAMSS_CSID_TG_VC_CFG(ver));

			/* 28:16 bytes per lines, 12:0 num of lines */
			val = ((num_bytes_per_line & 0x1fff) << 16) |
			      (num_lines & 0x1fff);
			writel_relaxed(val, csid->base +
				       CAMSS_CSID_TG_DT_n_CGG_0(ver, 0));

			dt = format->data_type;

			/* 5:0 data type */
			val = dt;
			writel_relaxed(val, csid->base +
				       CAMSS_CSID_TG_DT_n_CGG_1(ver, 0));

			/* 2:0 output test pattern */
			val = tg->payload_mode;
			writel_relaxed(val, csid->base +
				       CAMSS_CSID_TG_DT_n_CGG_2(ver, 0));

			df = format->decode_format;
		} else {
			struct v4l2_mbus_framefmt *f =
					&csid->fmt[MSM_CSID_PAD_SINK];
			const struct csid_format *format = csid_get_fmt_entry(
					csid->formats, csid->nformats, f->code);
			struct csid_phy_config *phy = &csid->phy;

			val = phy->lane_cnt - 1;
			val |= phy->lane_assign << 4;

			writel_relaxed(val,
				       csid->base + CAMSS_CSID_CORE_CTRL_0);

			val = phy->csiphy_id << 17;
			val |= 0x9;

			writel_relaxed(val,
				       csid->base + CAMSS_CSID_CORE_CTRL_1);

			dt = format->data_type;
			df = format->decode_format;
		}

		/* Config LUT */

		dt_shift = (cid % 4) * 8;

		val = readl_relaxed(csid->base +
				    CAMSS_CSID_CID_LUT_VC_n(ver, vc));
		val &= ~(0xff << dt_shift);
		val |= dt << dt_shift;
		writel_relaxed(val, csid->base +
			       CAMSS_CSID_CID_LUT_VC_n(ver, vc));

		val = CAMSS_CSID_CID_n_CFG_ISPIF_EN;
		val |= CAMSS_CSID_CID_n_CFG_RDI_EN;
		val |= df << CAMSS_CSID_CID_n_CFG_DECODE_FORMAT_SHIFT;
		val |= CAMSS_CSID_CID_n_CFG_RDI_MODE_RAW_DUMP;

		if (csid->camss->version == CAMSS_8x96) {
			u32 sink_code = csid->fmt[MSM_CSID_PAD_SINK].code;
			u32 src_code = csid->fmt[MSM_CSID_PAD_SRC].code;

			if ((sink_code == MEDIA_BUS_FMT_SBGGR10_1X10 &&
			     src_code == MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE) ||
			    (sink_code == MEDIA_BUS_FMT_Y10_1X10 &&
			     src_code == MEDIA_BUS_FMT_Y10_2X8_PADHI_LE)) {
				val |= CAMSS_CSID_CID_n_CFG_RDI_MODE_PLAIN_PACKING;
				val |= CAMSS_CSID_CID_n_CFG_PLAIN_FORMAT_16;
				val |= CAMSS_CSID_CID_n_CFG_PLAIN_ALIGNMENT_LSB;
			}
		}

		writel_relaxed(val, csid->base +
			       CAMSS_CSID_CID_n_CFG(ver, cid));

		if (tg->enabled) {
			val = CAMSS_CSID_TG_CTRL_ENABLE;
			writel_relaxed(val, csid->base +
				       CAMSS_CSID_TG_CTRL(ver));
		}
	} else {
		if (tg->enabled) {
			val = CAMSS_CSID_TG_CTRL_DISABLE;
			writel_relaxed(val, csid->base +
				       CAMSS_CSID_TG_CTRL(ver));
		}
	}

	return 0;
}