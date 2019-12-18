#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vpfe_device {size_t std_index; int /*<<< orphan*/  v4l2_dev; } ;
struct v4l2_fract {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_3__ {struct v4l2_fract pixelaspect; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct vpfe_device* video_drvdata (struct file*) ; 
 TYPE_1__* vpfe_standards ; 

__attribute__((used)) static int vpfe_g_pixelaspect(struct file *file, void *priv,
			      int type, struct v4l2_fract *f)
{
	struct vpfe_device *vpfe_dev = video_drvdata(file);

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_g_pixelaspect\n");

	if (type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;
	/* If std_index is invalid, then just return (== 1:1 aspect) */
	if (vpfe_dev->std_index >= ARRAY_SIZE(vpfe_standards))
		return 0;

	*f = vpfe_standards[vpfe_dev->std_index].pixelaspect;
	return 0;
}