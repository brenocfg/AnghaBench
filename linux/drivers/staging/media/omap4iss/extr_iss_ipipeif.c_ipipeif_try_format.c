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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {unsigned int width; unsigned int height; int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; } ;
struct iss_ipipeif_device {int dummy; } ;
typedef  enum v4l2_subdev_format_whence { ____Placeholder_v4l2_subdev_format_whence } v4l2_subdev_format_whence ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
#define  IPIPEIF_PAD_SINK 130 
#define  IPIPEIF_PAD_SOURCE_ISIF_SF 129 
#define  IPIPEIF_PAD_SOURCE_VP 128 
 int /*<<< orphan*/  MEDIA_BUS_FMT_SGRBG10_1X10 ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct v4l2_mbus_framefmt* __ipipeif_get_format (struct iss_ipipeif_device*,struct v4l2_subdev_pad_config*,int const,int) ; 
 void* clamp_t (int /*<<< orphan*/ ,unsigned int,int,int) ; 
 int /*<<< orphan*/ * ipipeif_fmts ; 
 int /*<<< orphan*/  memcpy (struct v4l2_mbus_framefmt*,struct v4l2_mbus_framefmt*,int) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static void
ipipeif_try_format(struct iss_ipipeif_device *ipipeif,
		   struct v4l2_subdev_pad_config *cfg, unsigned int pad,
		   struct v4l2_mbus_framefmt *fmt,
		   enum v4l2_subdev_format_whence which)
{
	struct v4l2_mbus_framefmt *format;
	unsigned int width = fmt->width;
	unsigned int height = fmt->height;
	unsigned int i;

	switch (pad) {
	case IPIPEIF_PAD_SINK:
		/* TODO: If the IPIPEIF output formatter pad is connected
		 * directly to the resizer, only YUV formats can be used.
		 */
		for (i = 0; i < ARRAY_SIZE(ipipeif_fmts); i++) {
			if (fmt->code == ipipeif_fmts[i])
				break;
		}

		/* If not found, use SGRBG10 as default */
		if (i >= ARRAY_SIZE(ipipeif_fmts))
			fmt->code = MEDIA_BUS_FMT_SGRBG10_1X10;

		/* Clamp the input size. */
		fmt->width = clamp_t(u32, width, 1, 8192);
		fmt->height = clamp_t(u32, height, 1, 8192);
		break;

	case IPIPEIF_PAD_SOURCE_ISIF_SF:
		format = __ipipeif_get_format(ipipeif, cfg, IPIPEIF_PAD_SINK,
					      which);
		memcpy(fmt, format, sizeof(*fmt));

		/* The data formatter truncates the number of horizontal output
		 * pixels to a multiple of 16. To avoid clipping data, allow
		 * callers to request an output size bigger than the input size
		 * up to the nearest multiple of 16.
		 */
		fmt->width = clamp_t(u32, width, 32, (fmt->width + 15) & ~15);
		fmt->width &= ~15;
		fmt->height = clamp_t(u32, height, 32, fmt->height);
		break;

	case IPIPEIF_PAD_SOURCE_VP:
		format = __ipipeif_get_format(ipipeif, cfg, IPIPEIF_PAD_SINK,
					      which);
		memcpy(fmt, format, sizeof(*fmt));

		fmt->width = clamp_t(u32, width, 32, fmt->width);
		fmt->height = clamp_t(u32, height, 32, fmt->height);
		break;
	}

	/* Data is written to memory unpacked, each 10-bit or 12-bit pixel is
	 * stored on 2 bytes.
	 */
	fmt->colorspace = V4L2_COLORSPACE_SRGB;
	fmt->field = V4L2_FIELD_NONE;
}