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
struct v4l2_rect {int left; int top; int width; int height; } ;
struct v4l2_mbus_framefmt {int width; unsigned int height; int /*<<< orphan*/  code; } ;
struct isp_format_info {scalar_t__ flavor; } ;
struct isp_ccdc_device {int dummy; } ;

/* Variables and functions */
 unsigned int CCDC_MIN_HEIGHT ; 
 unsigned int CCDC_MIN_WIDTH ; 
 scalar_t__ MEDIA_BUS_FMT_Y8_1X8 ; 
 int clamp_t (int /*<<< orphan*/ ,int,unsigned int,unsigned int) ; 
 struct isp_format_info* omap3isp_video_format_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static void ccdc_try_crop(struct isp_ccdc_device *ccdc,
			  const struct v4l2_mbus_framefmt *sink,
			  struct v4l2_rect *crop)
{
	const struct isp_format_info *info;
	unsigned int max_width;

	/* For Bayer formats, restrict left/top and width/height to even values
	 * to keep the Bayer pattern.
	 */
	info = omap3isp_video_format_info(sink->code);
	if (info->flavor != MEDIA_BUS_FMT_Y8_1X8) {
		crop->left &= ~1;
		crop->top &= ~1;
	}

	crop->left = clamp_t(u32, crop->left, 0, sink->width - CCDC_MIN_WIDTH);
	crop->top = clamp_t(u32, crop->top, 0, sink->height - CCDC_MIN_HEIGHT);

	/* The data formatter truncates the number of horizontal output pixels
	 * to a multiple of 16. To avoid clipping data, allow callers to request
	 * an output size bigger than the input size up to the nearest multiple
	 * of 16.
	 */
	max_width = (sink->width - crop->left + 15) & ~15;
	crop->width = clamp_t(u32, crop->width, CCDC_MIN_WIDTH, max_width)
		    & ~15;
	crop->height = clamp_t(u32, crop->height, CCDC_MIN_HEIGHT,
			       sink->height - crop->top);

	/* Odd width/height values don't make sense for Bayer formats. */
	if (info->flavor != MEDIA_BUS_FMT_Y8_1X8) {
		crop->width &= ~1;
		crop->height &= ~1;
	}
}