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
struct v4l2_mbus_framefmt {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; void* code; void* height; void* width; } ;
struct isp_ccp2_device {int /*<<< orphan*/  input; } ;
typedef  enum v4l2_subdev_format_whence { ____Placeholder_v4l2_subdev_format_whence } v4l2_subdev_format_whence ;

/* Variables and functions */
 int /*<<< orphan*/  CCP2_INPUT_MEMORY ; 
 int /*<<< orphan*/  CCP2_INPUT_SENSOR ; 
#define  CCP2_PAD_SINK 129 
#define  CCP2_PAD_SOURCE 128 
 int /*<<< orphan*/  ISPCCP2_DAT_SIZE_MAX ; 
 int /*<<< orphan*/  ISPCCP2_DAT_SIZE_MIN ; 
 int /*<<< orphan*/  ISPCCP2_DAT_START_MAX ; 
 int /*<<< orphan*/  ISPCCP2_DAT_START_MIN ; 
 int /*<<< orphan*/  ISPCCP2_LCM_HSIZE_COUNT_MAX ; 
 int /*<<< orphan*/  ISPCCP2_LCM_HSIZE_COUNT_MIN ; 
 int /*<<< orphan*/  ISPCCP2_LCM_VSIZE_MAX ; 
 int /*<<< orphan*/  ISPCCP2_LCM_VSIZE_MIN ; 
 void* MEDIA_BUS_FMT_SGRBG10_1X10 ; 
 void* MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8 ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct v4l2_mbus_framefmt* __ccp2_get_format (struct isp_ccp2_device*,struct v4l2_subdev_pad_config*,int const,int) ; 
 void* clamp_t (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct v4l2_mbus_framefmt*,struct v4l2_mbus_framefmt*,int) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static void ccp2_try_format(struct isp_ccp2_device *ccp2,
			       struct v4l2_subdev_pad_config *cfg, unsigned int pad,
			       struct v4l2_mbus_framefmt *fmt,
			       enum v4l2_subdev_format_whence which)
{
	struct v4l2_mbus_framefmt *format;

	switch (pad) {
	case CCP2_PAD_SINK:
		if (fmt->code != MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8)
			fmt->code = MEDIA_BUS_FMT_SGRBG10_1X10;

		if (ccp2->input == CCP2_INPUT_SENSOR) {
			fmt->width = clamp_t(u32, fmt->width,
					     ISPCCP2_DAT_START_MIN,
					     ISPCCP2_DAT_START_MAX);
			fmt->height = clamp_t(u32, fmt->height,
					      ISPCCP2_DAT_SIZE_MIN,
					      ISPCCP2_DAT_SIZE_MAX);
		} else if (ccp2->input == CCP2_INPUT_MEMORY) {
			fmt->width = clamp_t(u32, fmt->width,
					     ISPCCP2_LCM_HSIZE_COUNT_MIN,
					     ISPCCP2_LCM_HSIZE_COUNT_MAX);
			fmt->height = clamp_t(u32, fmt->height,
					      ISPCCP2_LCM_VSIZE_MIN,
					      ISPCCP2_LCM_VSIZE_MAX);
		}
		break;

	case CCP2_PAD_SOURCE:
		/* Source format - copy sink format and change pixel code
		 * to SGRBG10_1X10 as we don't support CCP2 write to memory.
		 * When CCP2 write to memory feature will be added this
		 * should be changed properly.
		 */
		format = __ccp2_get_format(ccp2, cfg, CCP2_PAD_SINK, which);
		memcpy(fmt, format, sizeof(*fmt));
		fmt->code = MEDIA_BUS_FMT_SGRBG10_1X10;
		break;
	}

	fmt->field = V4L2_FIELD_NONE;
	fmt->colorspace = V4L2_COLORSPACE_SRGB;
}