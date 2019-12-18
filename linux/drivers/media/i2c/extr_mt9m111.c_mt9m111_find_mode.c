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
struct v4l2_rect {int width; int height; } ;
struct mt9m111_mode_info {unsigned int max_fps; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mt9m111 {int /*<<< orphan*/ * ctx; TYPE_1__ subdev; struct v4l2_rect rect; } ;

/* Variables and functions */
 int MT9M111_MAX_HEIGHT ; 
 int MT9M111_MAX_WIDTH ; 
 int MT9M111_MODE_QSXGA_30FPS ; 
 int MT9M111_MODE_SXGA_15FPS ; 
 int MT9M111_NUM_MODES ; 
 unsigned int abs (unsigned int) ; 
 int /*<<< orphan*/  context_a ; 
 int /*<<< orphan*/  context_b ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 struct mt9m111_mode_info* mt9m111_mode_data ; 

__attribute__((used)) static const struct mt9m111_mode_info *
mt9m111_find_mode(struct mt9m111 *mt9m111, unsigned int req_fps,
		  unsigned int width, unsigned int height)
{
	const struct mt9m111_mode_info *mode;
	struct v4l2_rect *sensor_rect = &mt9m111->rect;
	unsigned int gap, gap_best = (unsigned int) -1;
	int i, best_gap_idx = MT9M111_MODE_SXGA_15FPS;
	bool skip_30fps = false;

	/*
	 * The fps selection is based on the row, column skipping mechanism.
	 * So ensure that the sensor window is set to default else the fps
	 * aren't calculated correctly within the sensor hw.
	 */
	if (sensor_rect->width != MT9M111_MAX_WIDTH ||
	    sensor_rect->height != MT9M111_MAX_HEIGHT) {
		dev_info(mt9m111->subdev.dev,
			 "Framerate selection is not supported for cropped "
			 "images\n");
		return NULL;
	}

	/* 30fps only supported for images not exceeding 640x512 */
	if (width > MT9M111_MAX_WIDTH / 2 || height > MT9M111_MAX_HEIGHT / 2) {
		dev_dbg(mt9m111->subdev.dev,
			"Framerates > 15fps are supported only for images "
			"not exceeding 640x512\n");
		skip_30fps = true;
	}

	/* find best matched fps */
	for (i = 0; i < MT9M111_NUM_MODES; i++) {
		unsigned int fps = mt9m111_mode_data[i].max_fps;

		if (fps == 30 && skip_30fps)
			continue;

		gap = abs(fps - req_fps);
		if (gap < gap_best) {
			best_gap_idx = i;
			gap_best = gap;
		}
	}

	/*
	 * Use context a/b default timing values instead of calculate blanking
	 * timing values.
	 */
	mode = &mt9m111_mode_data[best_gap_idx];
	mt9m111->ctx = (best_gap_idx == MT9M111_MODE_QSXGA_30FPS) ? &context_a :
								    &context_b;
	return mode;
}