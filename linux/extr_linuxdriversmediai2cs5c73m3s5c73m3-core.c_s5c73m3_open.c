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
struct v4l2_subdev_fh {int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S5C73M3_ISP_FMT ; 
 int /*<<< orphan*/  S5C73M3_ISP_PAD ; 
 int /*<<< orphan*/  S5C73M3_JPEG_FMT ; 
 int /*<<< orphan*/  S5C73M3_JPEG_PAD ; 
 int /*<<< orphan*/  s5c73m3_fill_mbus_fmt (struct v4l2_mbus_framefmt*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * s5c73m3_isp_resolutions ; 
 int /*<<< orphan*/ * s5c73m3_jpeg_resolutions ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5c73m3_open(struct v4l2_subdev *sd, struct v4l2_subdev_fh *fh)
{
	struct v4l2_mbus_framefmt *mf;

	mf = v4l2_subdev_get_try_format(sd, fh->pad, S5C73M3_ISP_PAD);
	s5c73m3_fill_mbus_fmt(mf, &s5c73m3_isp_resolutions[1],
						S5C73M3_ISP_FMT);

	mf = v4l2_subdev_get_try_format(sd, fh->pad, S5C73M3_JPEG_PAD);
	s5c73m3_fill_mbus_fmt(mf, &s5c73m3_jpeg_resolutions[1],
					S5C73M3_JPEG_FMT);

	return 0;
}