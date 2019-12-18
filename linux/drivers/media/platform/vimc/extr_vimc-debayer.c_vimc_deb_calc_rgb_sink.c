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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {unsigned int height; unsigned int width; } ;
struct vimc_deb_device {TYPE_3__ sd; int /*<<< orphan*/  dev; int /*<<< orphan*/  sink_bpp; TYPE_2__ sink_fmt; TYPE_1__* sink_pix_map; } ;
typedef  enum vimc_deb_rgb_colors { ____Placeholder_vimc_deb_rgb_colors } vimc_deb_rgb_colors ;
struct TYPE_4__ {int** order; } ;

/* Variables and functions */
 unsigned int VIMC_FRAME_INDEX (unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int deb_mean_win_size ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int const,unsigned int const,...) ; 
 unsigned int vimc_deb_get_val (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vimc_deb_calc_rgb_sink(struct vimc_deb_device *vdeb,
				   const u8 *frame,
				   const unsigned int lin,
				   const unsigned int col,
				   unsigned int rgb[3])
{
	unsigned int i, seek, wlin, wcol;
	unsigned int n_rgb[3] = {0, 0, 0};

	for (i = 0; i < 3; i++)
		rgb[i] = 0;

	/*
	 * Calculate how many we need to subtract to get to the pixel in
	 * the top left corner of the mean window (considering the current
	 * pixel as the center)
	 */
	seek = deb_mean_win_size / 2;

	/* Sum the values of the colors in the mean window */

	dev_dbg(vdeb->dev,
		"deb: %s: --- Calc pixel %dx%d, window mean %d, seek %d ---\n",
		vdeb->sd.name, lin, col, vdeb->sink_fmt.height, seek);

	/*
	 * Iterate through all the lines in the mean window, start
	 * with zero if the pixel is outside the frame and don't pass
	 * the height when the pixel is in the bottom border of the
	 * frame
	 */
	for (wlin = seek > lin ? 0 : lin - seek;
	     wlin < lin + seek + 1 && wlin < vdeb->sink_fmt.height;
	     wlin++) {

		/*
		 * Iterate through all the columns in the mean window, start
		 * with zero if the pixel is outside the frame and don't pass
		 * the width when the pixel is in the right border of the
		 * frame
		 */
		for (wcol = seek > col ? 0 : col - seek;
		     wcol < col + seek + 1 && wcol < vdeb->sink_fmt.width;
		     wcol++) {
			enum vimc_deb_rgb_colors color;
			unsigned int index;

			/* Check which color this pixel is */
			color = vdeb->sink_pix_map->order[wlin % 2][wcol % 2];

			index = VIMC_FRAME_INDEX(wlin, wcol,
						 vdeb->sink_fmt.width,
						 vdeb->sink_bpp);

			dev_dbg(vdeb->dev,
				"deb: %s: RGB CALC: frame index %d, win pos %dx%d, color %d\n",
				vdeb->sd.name, index, wlin, wcol, color);

			/* Get its value */
			rgb[color] = rgb[color] +
				vimc_deb_get_val(&frame[index], vdeb->sink_bpp);

			/* Save how many values we already added */
			n_rgb[color]++;

			dev_dbg(vdeb->dev, "deb: %s: RGB CALC: val %d, n %d\n",
				vdeb->sd.name, rgb[color], n_rgb[color]);
		}
	}

	/* Calculate the mean */
	for (i = 0; i < 3; i++) {
		dev_dbg(vdeb->dev,
			"deb: %s: PRE CALC: %dx%d Color %d, val %d, n %d\n",
			vdeb->sd.name, lin, col, i, rgb[i], n_rgb[i]);

		if (n_rgb[i])
			rgb[i] = rgb[i] / n_rgb[i];

		dev_dbg(vdeb->dev,
			"deb: %s: FINAL CALC: %dx%d Color %d, val %d\n",
			vdeb->sd.name, lin, col, i, rgb[i]);
	}
}