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
struct v4l2_frmsizeenum {size_t index; int /*<<< orphan*/  discrete; int /*<<< orphan*/  type; int /*<<< orphan*/  pixel_format; } ;
struct s2255_vc {int std; } ;
struct s2255_fmt {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NUM_SIZE_ENUMS ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_DISCRETE ; 
 int V4L2_STD_525_60 ; 
 struct s2255_fmt* format_by_fourcc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ntsc_sizes ; 
 int /*<<< orphan*/ * pal_sizes ; 
 struct s2255_vc* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_enum_framesizes(struct file *file, void *priv,
			    struct v4l2_frmsizeenum *fe)
{
	struct s2255_vc *vc = video_drvdata(file);
	int is_ntsc = vc->std & V4L2_STD_525_60;
	const struct s2255_fmt *fmt;

	if (fe->index >= NUM_SIZE_ENUMS)
		return -EINVAL;

	fmt = format_by_fourcc(fe->pixel_format);
	if (fmt == NULL)
		return -EINVAL;
	fe->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	fe->discrete = is_ntsc ?  ntsc_sizes[fe->index] : pal_sizes[fe->index];
	return 0;
}