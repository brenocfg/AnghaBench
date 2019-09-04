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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct v4l2_format {int dummy; } ;
struct tw686x_video_channel {int /*<<< orphan*/  fps; int /*<<< orphan*/  vidq; int /*<<< orphan*/  video_standard; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  tw686x_g_fmt_vid_cap (struct file*,void*,struct v4l2_format*) ; 
 int /*<<< orphan*/  tw686x_s_fmt_vid_cap (struct file*,void*,struct v4l2_format*) ; 
 int /*<<< orphan*/  tw686x_set_framerate (struct tw686x_video_channel*,int /*<<< orphan*/ ) ; 
 int tw686x_set_standard (struct tw686x_video_channel*,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct tw686x_video_channel* video_drvdata (struct file*) ; 

__attribute__((used)) static int tw686x_s_std(struct file *file, void *priv, v4l2_std_id id)
{
	struct tw686x_video_channel *vc = video_drvdata(file);
	struct v4l2_format f;
	int ret;

	if (vc->video_standard == id)
		return 0;

	if (vb2_is_busy(&vc->vidq))
		return -EBUSY;

	ret = tw686x_set_standard(vc, id);
	if (ret)
		return ret;
	/*
	 * Adjust format after V4L2_STD_525_60/V4L2_STD_625_50 change,
	 * calling g_fmt and s_fmt will sanitize the height
	 * according to the standard.
	 */
	tw686x_g_fmt_vid_cap(file, priv, &f);
	tw686x_s_fmt_vid_cap(file, priv, &f);

	/*
	 * Frame decimation depends on the chosen standard,
	 * so reset it to the current value.
	 */
	tw686x_set_framerate(vc, vc->fps);
	return 0;
}