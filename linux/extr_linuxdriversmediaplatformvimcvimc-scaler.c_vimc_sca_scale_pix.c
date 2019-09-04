#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {unsigned int const width; } ;
struct vimc_sca_device {unsigned int const bpp; scalar_t__ src_line_size; int /*<<< orphan*/ * src_frame; TYPE_2__ sd; int /*<<< orphan*/  dev; TYPE_1__ sink_fmt; } ;

/* Variables and functions */
 unsigned int VIMC_FRAME_INDEX (unsigned int const,unsigned int const,unsigned int const,unsigned int const) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int const,...) ; 
 unsigned int const sca_mult ; 
 int /*<<< orphan*/  vimc_sca_fill_pix (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static void vimc_sca_scale_pix(const struct vimc_sca_device *const vsca,
			       const unsigned int lin, const unsigned int col,
			       const u8 *const sink_frame)
{
	unsigned int i, j, index;
	const u8 *pixel;

	/* Point to the pixel value in position (lin, col) in the sink frame */
	index = VIMC_FRAME_INDEX(lin, col,
				 vsca->sink_fmt.width,
				 vsca->bpp);
	pixel = &sink_frame[index];

	dev_dbg(vsca->dev,
		"sca: %s: --- scale_pix sink pos %dx%d, index %d ---\n",
		vsca->sd.name, lin, col, index);

	/* point to the place we are going to put the first pixel
	 * in the scaled src frame
	 */
	index = VIMC_FRAME_INDEX(lin * sca_mult, col * sca_mult,
				 vsca->sink_fmt.width * sca_mult, vsca->bpp);

	dev_dbg(vsca->dev, "sca: %s: scale_pix src pos %dx%d, index %d\n",
		vsca->sd.name, lin * sca_mult, col * sca_mult, index);

	/* Repeat this pixel mult times */
	for (i = 0; i < sca_mult; i++) {
		/* Iterate through each beginning of a
		 * pixel repetition in a line
		 */
		for (j = 0; j < sca_mult * vsca->bpp; j += vsca->bpp) {
			dev_dbg(vsca->dev,
				"sca: %s: sca: scale_pix src pos %d\n",
				vsca->sd.name, index + j);

			/* copy the pixel to the position index + j */
			vimc_sca_fill_pix(&vsca->src_frame[index + j],
					  pixel, vsca->bpp);
		}

		/* move the index to the next line */
		index += vsca->src_line_size;
	}
}