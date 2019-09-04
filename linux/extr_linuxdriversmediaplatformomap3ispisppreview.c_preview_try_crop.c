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
struct v4l2_mbus_framefmt {unsigned int width; unsigned int height; scalar_t__ code; } ;
struct isp_prev_device {scalar_t__ input; } ;

/* Variables and functions */
 scalar_t__ MEDIA_BUS_FMT_Y10_1X10 ; 
 scalar_t__ MEDIA_BUS_FMT_Y8_1X8 ; 
 scalar_t__ PREVIEW_INPUT_CCDC ; 
 unsigned int PREV_MARGIN_BOTTOM ; 
 unsigned int PREV_MARGIN_LEFT ; 
 unsigned int PREV_MARGIN_RIGHT ; 
 unsigned int PREV_MARGIN_TOP ; 
 unsigned int PREV_MIN_OUT_HEIGHT ; 
 unsigned int PREV_MIN_OUT_WIDTH ; 
 void* clamp_t (int /*<<< orphan*/ ,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static void preview_try_crop(struct isp_prev_device *prev,
			     const struct v4l2_mbus_framefmt *sink,
			     struct v4l2_rect *crop)
{
	unsigned int left = PREV_MARGIN_LEFT;
	unsigned int right = sink->width - PREV_MARGIN_RIGHT;
	unsigned int top = PREV_MARGIN_TOP;
	unsigned int bottom = sink->height - PREV_MARGIN_BOTTOM;

	/* When processing data on-the-fly from the CCDC, at least 2 pixels must
	 * be cropped from the left and right sides of the image. As we don't
	 * know which filters will be enabled, increase the left and right
	 * margins by two.
	 */
	if (prev->input == PREVIEW_INPUT_CCDC) {
		left += 2;
		right -= 2;
	}

	/* The CFA filter crops 4 lines and 4 columns in Bayer mode, and 2 lines
	 * and no columns in other modes. Increase the margins based on the sink
	 * format.
	 */
	if (sink->code != MEDIA_BUS_FMT_Y8_1X8 &&
	    sink->code != MEDIA_BUS_FMT_Y10_1X10) {
		left += 2;
		right -= 2;
		top += 2;
		bottom -= 2;
	}

	/* Restrict left/top to even values to keep the Bayer pattern. */
	crop->left &= ~1;
	crop->top &= ~1;

	crop->left = clamp_t(u32, crop->left, left, right - PREV_MIN_OUT_WIDTH);
	crop->top = clamp_t(u32, crop->top, top, bottom - PREV_MIN_OUT_HEIGHT);
	crop->width = clamp_t(u32, crop->width, PREV_MIN_OUT_WIDTH,
			      right - crop->left);
	crop->height = clamp_t(u32, crop->height, PREV_MIN_OUT_HEIGHT,
			       bottom - crop->top);
}