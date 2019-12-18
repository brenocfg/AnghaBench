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
typedef  size_t u16 ;
struct video_mux {size_t active; int /*<<< orphan*/  lock; struct v4l2_mbus_framefmt* format_mbus; struct media_pad* pads; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int code; scalar_t__ field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_subdev_format {size_t pad; struct v4l2_mbus_framefmt format; int /*<<< orphan*/  which; } ;
struct TYPE_2__ {size_t num_pads; } ;
struct v4l2_subdev {TYPE_1__ entity; } ;
struct media_pad {int flags; size_t index; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MEDIA_BUS_FMT_AHSV8888_1X32 215 
#define  MEDIA_BUS_FMT_ARGB8888_1X32 214 
#define  MEDIA_BUS_FMT_AYUV8_1X32 213 
#define  MEDIA_BUS_FMT_BGR565_2X8_BE 212 
#define  MEDIA_BUS_FMT_BGR565_2X8_LE 211 
#define  MEDIA_BUS_FMT_BGR888_1X24 210 
#define  MEDIA_BUS_FMT_GBR888_1X24 209 
#define  MEDIA_BUS_FMT_JPEG_1X8 208 
#define  MEDIA_BUS_FMT_RBG888_1X24 207 
#define  MEDIA_BUS_FMT_RGB101010_1X30 206 
#define  MEDIA_BUS_FMT_RGB121212_1X36 205 
#define  MEDIA_BUS_FMT_RGB161616_1X48 204 
#define  MEDIA_BUS_FMT_RGB444_1X12 203 
#define  MEDIA_BUS_FMT_RGB444_2X8_PADHI_BE 202 
#define  MEDIA_BUS_FMT_RGB444_2X8_PADHI_LE 201 
#define  MEDIA_BUS_FMT_RGB555_2X8_PADHI_BE 200 
#define  MEDIA_BUS_FMT_RGB555_2X8_PADHI_LE 199 
#define  MEDIA_BUS_FMT_RGB565_1X16 198 
#define  MEDIA_BUS_FMT_RGB565_2X8_BE 197 
#define  MEDIA_BUS_FMT_RGB565_2X8_LE 196 
#define  MEDIA_BUS_FMT_RGB666_1X18 195 
#define  MEDIA_BUS_FMT_RGB666_1X24_CPADHI 194 
#define  MEDIA_BUS_FMT_RGB888_1X24 193 
#define  MEDIA_BUS_FMT_RGB888_1X32_PADHI 192 
#define  MEDIA_BUS_FMT_RGB888_2X12_BE 191 
#define  MEDIA_BUS_FMT_RGB888_2X12_LE 190 
#define  MEDIA_BUS_FMT_SBGGR10_1X10 189 
#define  MEDIA_BUS_FMT_SBGGR12_1X12 188 
#define  MEDIA_BUS_FMT_SBGGR14_1X14 187 
#define  MEDIA_BUS_FMT_SBGGR16_1X16 186 
#define  MEDIA_BUS_FMT_SBGGR8_1X8 185 
#define  MEDIA_BUS_FMT_SGBRG10_1X10 184 
#define  MEDIA_BUS_FMT_SGBRG12_1X12 183 
#define  MEDIA_BUS_FMT_SGBRG14_1X14 182 
#define  MEDIA_BUS_FMT_SGBRG16_1X16 181 
#define  MEDIA_BUS_FMT_SGBRG8_1X8 180 
#define  MEDIA_BUS_FMT_SGRBG10_1X10 179 
#define  MEDIA_BUS_FMT_SGRBG12_1X12 178 
#define  MEDIA_BUS_FMT_SGRBG14_1X14 177 
#define  MEDIA_BUS_FMT_SGRBG16_1X16 176 
#define  MEDIA_BUS_FMT_SGRBG8_1X8 175 
#define  MEDIA_BUS_FMT_SRGGB10_1X10 174 
#define  MEDIA_BUS_FMT_SRGGB12_1X12 173 
#define  MEDIA_BUS_FMT_SRGGB14_1X14 172 
#define  MEDIA_BUS_FMT_SRGGB16_1X16 171 
#define  MEDIA_BUS_FMT_SRGGB8_1X8 170 
#define  MEDIA_BUS_FMT_UV8_1X8 169 
#define  MEDIA_BUS_FMT_UYVY10_1X20 168 
#define  MEDIA_BUS_FMT_UYVY10_2X10 167 
#define  MEDIA_BUS_FMT_UYVY12_1X24 166 
#define  MEDIA_BUS_FMT_UYVY12_2X12 165 
#define  MEDIA_BUS_FMT_UYVY8_1X16 164 
#define  MEDIA_BUS_FMT_UYVY8_1_5X8 163 
#define  MEDIA_BUS_FMT_UYVY8_2X8 162 
#define  MEDIA_BUS_FMT_UYYVYY10_0_5X30 161 
#define  MEDIA_BUS_FMT_UYYVYY12_0_5X36 160 
#define  MEDIA_BUS_FMT_UYYVYY16_0_5X48 159 
#define  MEDIA_BUS_FMT_UYYVYY8_0_5X24 158 
#define  MEDIA_BUS_FMT_VUY8_1X24 157 
#define  MEDIA_BUS_FMT_VYUY10_1X20 156 
#define  MEDIA_BUS_FMT_VYUY10_2X10 155 
#define  MEDIA_BUS_FMT_VYUY12_1X24 154 
#define  MEDIA_BUS_FMT_VYUY12_2X12 153 
#define  MEDIA_BUS_FMT_VYUY8_1X16 152 
#define  MEDIA_BUS_FMT_VYUY8_1_5X8 151 
#define  MEDIA_BUS_FMT_VYUY8_2X8 150 
#define  MEDIA_BUS_FMT_Y10_1X10 149 
#define  MEDIA_BUS_FMT_Y12_1X12 148 
#define  MEDIA_BUS_FMT_Y8_1X8 147 
#define  MEDIA_BUS_FMT_YDYUYDYV8_1X16 146 
#define  MEDIA_BUS_FMT_YUV10_1X30 145 
#define  MEDIA_BUS_FMT_YUV12_1X36 144 
#define  MEDIA_BUS_FMT_YUV16_1X48 143 
#define  MEDIA_BUS_FMT_YUV8_1X24 142 
#define  MEDIA_BUS_FMT_YUYV10_1X20 141 
#define  MEDIA_BUS_FMT_YUYV10_2X10 140 
#define  MEDIA_BUS_FMT_YUYV12_1X24 139 
#define  MEDIA_BUS_FMT_YUYV12_2X12 138 
#define  MEDIA_BUS_FMT_YUYV8_1X16 137 
#define  MEDIA_BUS_FMT_YUYV8_1_5X8 136 
#define  MEDIA_BUS_FMT_YUYV8_2X8 135 
#define  MEDIA_BUS_FMT_YVYU10_1X20 134 
#define  MEDIA_BUS_FMT_YVYU10_2X10 133 
#define  MEDIA_BUS_FMT_YVYU12_1X24 132 
#define  MEDIA_BUS_FMT_YVYU12_2X12 131 
#define  MEDIA_BUS_FMT_YVYU8_1X16 130 
#define  MEDIA_BUS_FMT_YVYU8_1_5X8 129 
#define  MEDIA_BUS_FMT_YVYU8_2X8 128 
 int MEDIA_PAD_FL_SINK ; 
 int MEDIA_PAD_FL_SOURCE ; 
 scalar_t__ V4L2_FIELD_ANY ; 
 scalar_t__ V4L2_FIELD_NONE ; 
 struct v4l2_mbus_framefmt* __video_mux_get_pad_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct video_mux* v4l2_subdev_to_video_mux (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l_bound_align_image (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int video_mux_set_format(struct v4l2_subdev *sd,
			    struct v4l2_subdev_pad_config *cfg,
			    struct v4l2_subdev_format *sdformat)
{
	struct video_mux *vmux = v4l2_subdev_to_video_mux(sd);
	struct v4l2_mbus_framefmt *mbusformat, *source_mbusformat;
	struct media_pad *pad = &vmux->pads[sdformat->pad];
	u16 source_pad = sd->entity.num_pads - 1;

	mbusformat = __video_mux_get_pad_format(sd, cfg, sdformat->pad,
					    sdformat->which);
	if (!mbusformat)
		return -EINVAL;

	source_mbusformat = __video_mux_get_pad_format(sd, cfg, source_pad,
						       sdformat->which);
	if (!source_mbusformat)
		return -EINVAL;

	/* No size limitations except V4L2 compliance requirements */
	v4l_bound_align_image(&sdformat->format.width, 1, 65536, 0,
			      &sdformat->format.height, 1, 65536, 0, 0);

	/* All formats except LVDS and vendor specific formats are acceptable */
	switch (sdformat->format.code) {
	case MEDIA_BUS_FMT_RGB444_1X12:
	case MEDIA_BUS_FMT_RGB444_2X8_PADHI_BE:
	case MEDIA_BUS_FMT_RGB444_2X8_PADHI_LE:
	case MEDIA_BUS_FMT_RGB555_2X8_PADHI_BE:
	case MEDIA_BUS_FMT_RGB555_2X8_PADHI_LE:
	case MEDIA_BUS_FMT_RGB565_1X16:
	case MEDIA_BUS_FMT_BGR565_2X8_BE:
	case MEDIA_BUS_FMT_BGR565_2X8_LE:
	case MEDIA_BUS_FMT_RGB565_2X8_BE:
	case MEDIA_BUS_FMT_RGB565_2X8_LE:
	case MEDIA_BUS_FMT_RGB666_1X18:
	case MEDIA_BUS_FMT_RBG888_1X24:
	case MEDIA_BUS_FMT_RGB666_1X24_CPADHI:
	case MEDIA_BUS_FMT_BGR888_1X24:
	case MEDIA_BUS_FMT_GBR888_1X24:
	case MEDIA_BUS_FMT_RGB888_1X24:
	case MEDIA_BUS_FMT_RGB888_2X12_BE:
	case MEDIA_BUS_FMT_RGB888_2X12_LE:
	case MEDIA_BUS_FMT_ARGB8888_1X32:
	case MEDIA_BUS_FMT_RGB888_1X32_PADHI:
	case MEDIA_BUS_FMT_RGB101010_1X30:
	case MEDIA_BUS_FMT_RGB121212_1X36:
	case MEDIA_BUS_FMT_RGB161616_1X48:
	case MEDIA_BUS_FMT_Y8_1X8:
	case MEDIA_BUS_FMT_UV8_1X8:
	case MEDIA_BUS_FMT_UYVY8_1_5X8:
	case MEDIA_BUS_FMT_VYUY8_1_5X8:
	case MEDIA_BUS_FMT_YUYV8_1_5X8:
	case MEDIA_BUS_FMT_YVYU8_1_5X8:
	case MEDIA_BUS_FMT_UYVY8_2X8:
	case MEDIA_BUS_FMT_VYUY8_2X8:
	case MEDIA_BUS_FMT_YUYV8_2X8:
	case MEDIA_BUS_FMT_YVYU8_2X8:
	case MEDIA_BUS_FMT_Y10_1X10:
	case MEDIA_BUS_FMT_UYVY10_2X10:
	case MEDIA_BUS_FMT_VYUY10_2X10:
	case MEDIA_BUS_FMT_YUYV10_2X10:
	case MEDIA_BUS_FMT_YVYU10_2X10:
	case MEDIA_BUS_FMT_Y12_1X12:
	case MEDIA_BUS_FMT_UYVY12_2X12:
	case MEDIA_BUS_FMT_VYUY12_2X12:
	case MEDIA_BUS_FMT_YUYV12_2X12:
	case MEDIA_BUS_FMT_YVYU12_2X12:
	case MEDIA_BUS_FMT_UYVY8_1X16:
	case MEDIA_BUS_FMT_VYUY8_1X16:
	case MEDIA_BUS_FMT_YUYV8_1X16:
	case MEDIA_BUS_FMT_YVYU8_1X16:
	case MEDIA_BUS_FMT_YDYUYDYV8_1X16:
	case MEDIA_BUS_FMT_UYVY10_1X20:
	case MEDIA_BUS_FMT_VYUY10_1X20:
	case MEDIA_BUS_FMT_YUYV10_1X20:
	case MEDIA_BUS_FMT_YVYU10_1X20:
	case MEDIA_BUS_FMT_VUY8_1X24:
	case MEDIA_BUS_FMT_YUV8_1X24:
	case MEDIA_BUS_FMT_UYYVYY8_0_5X24:
	case MEDIA_BUS_FMT_UYVY12_1X24:
	case MEDIA_BUS_FMT_VYUY12_1X24:
	case MEDIA_BUS_FMT_YUYV12_1X24:
	case MEDIA_BUS_FMT_YVYU12_1X24:
	case MEDIA_BUS_FMT_YUV10_1X30:
	case MEDIA_BUS_FMT_UYYVYY10_0_5X30:
	case MEDIA_BUS_FMT_AYUV8_1X32:
	case MEDIA_BUS_FMT_UYYVYY12_0_5X36:
	case MEDIA_BUS_FMT_YUV12_1X36:
	case MEDIA_BUS_FMT_YUV16_1X48:
	case MEDIA_BUS_FMT_UYYVYY16_0_5X48:
	case MEDIA_BUS_FMT_JPEG_1X8:
	case MEDIA_BUS_FMT_AHSV8888_1X32:
	case MEDIA_BUS_FMT_SBGGR8_1X8:
	case MEDIA_BUS_FMT_SGBRG8_1X8:
	case MEDIA_BUS_FMT_SGRBG8_1X8:
	case MEDIA_BUS_FMT_SRGGB8_1X8:
	case MEDIA_BUS_FMT_SBGGR10_1X10:
	case MEDIA_BUS_FMT_SGBRG10_1X10:
	case MEDIA_BUS_FMT_SGRBG10_1X10:
	case MEDIA_BUS_FMT_SRGGB10_1X10:
	case MEDIA_BUS_FMT_SBGGR12_1X12:
	case MEDIA_BUS_FMT_SGBRG12_1X12:
	case MEDIA_BUS_FMT_SGRBG12_1X12:
	case MEDIA_BUS_FMT_SRGGB12_1X12:
	case MEDIA_BUS_FMT_SBGGR14_1X14:
	case MEDIA_BUS_FMT_SGBRG14_1X14:
	case MEDIA_BUS_FMT_SGRBG14_1X14:
	case MEDIA_BUS_FMT_SRGGB14_1X14:
	case MEDIA_BUS_FMT_SBGGR16_1X16:
	case MEDIA_BUS_FMT_SGBRG16_1X16:
	case MEDIA_BUS_FMT_SGRBG16_1X16:
	case MEDIA_BUS_FMT_SRGGB16_1X16:
		break;
	default:
		sdformat->format.code = MEDIA_BUS_FMT_Y8_1X8;
		break;
	}
	if (sdformat->format.field == V4L2_FIELD_ANY)
		sdformat->format.field = V4L2_FIELD_NONE;

	mutex_lock(&vmux->lock);

	/* Source pad mirrors active sink pad, no limitations on sink pads */
	if ((pad->flags & MEDIA_PAD_FL_SOURCE) && vmux->active >= 0)
		sdformat->format = vmux->format_mbus[vmux->active];

	*mbusformat = sdformat->format;

	/* Propagate the format from an active sink to source */
	if ((pad->flags & MEDIA_PAD_FL_SINK) && (pad->index == vmux->active))
		*source_mbusformat = sdformat->format;

	mutex_unlock(&vmux->lock);

	return 0;
}