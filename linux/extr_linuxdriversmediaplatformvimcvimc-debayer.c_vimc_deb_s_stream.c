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
struct vimc_pix_map {unsigned int bpp; } ;
struct TYPE_2__ {unsigned int width; unsigned int height; int /*<<< orphan*/  code; } ;
struct vimc_deb_device {unsigned int sink_bpp; int /*<<< orphan*/ * src_frame; TYPE_1__ sink_fmt; int /*<<< orphan*/  sink_pix_map; int /*<<< orphan*/  src_code; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct vimc_deb_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vimc_deb_pix_map_by_code (int /*<<< orphan*/ ) ; 
 struct vimc_pix_map* vimc_pix_map_by_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vmalloc (unsigned int) ; 

__attribute__((used)) static int vimc_deb_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct vimc_deb_device *vdeb = v4l2_get_subdevdata(sd);

	if (enable) {
		const struct vimc_pix_map *vpix;
		unsigned int frame_size;

		if (vdeb->src_frame)
			return 0;

		/* Calculate the frame size of the source pad */
		vpix = vimc_pix_map_by_code(vdeb->src_code);
		frame_size = vdeb->sink_fmt.width * vdeb->sink_fmt.height *
				vpix->bpp;

		/* Save the bytes per pixel of the sink */
		vpix = vimc_pix_map_by_code(vdeb->sink_fmt.code);
		vdeb->sink_bpp = vpix->bpp;

		/* Get the corresponding pixel map from the table */
		vdeb->sink_pix_map =
			vimc_deb_pix_map_by_code(vdeb->sink_fmt.code);

		/*
		 * Allocate the frame buffer. Use vmalloc to be able to
		 * allocate a large amount of memory
		 */
		vdeb->src_frame = vmalloc(frame_size);
		if (!vdeb->src_frame)
			return -ENOMEM;

	} else {
		if (!vdeb->src_frame)
			return 0;

		vfree(vdeb->src_frame);
		vdeb->src_frame = NULL;
	}

	return 0;
}