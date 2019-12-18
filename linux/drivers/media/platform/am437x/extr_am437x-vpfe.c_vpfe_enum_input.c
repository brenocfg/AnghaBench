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
struct vpfe_subdev_info {struct v4l2_input* inputs; } ;
struct vpfe_device {TYPE_1__* cfg; } ;
struct v4l2_input {int /*<<< orphan*/  index; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct vpfe_subdev_info* sub_devs; } ;

/* Variables and functions */
 int EINVAL ; 
 struct vpfe_device* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vpfe_dbg (int,struct vpfe_device*,char*) ; 
 scalar_t__ vpfe_get_subdev_input_index (struct vpfe_device*,int*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpfe_enum_input(struct file *file, void *priv,
			   struct v4l2_input *inp)
{
	struct vpfe_device *vpfe = video_drvdata(file);
	struct vpfe_subdev_info *sdinfo;
	int subdev, index;

	vpfe_dbg(2, vpfe, "vpfe_enum_input\n");

	if (vpfe_get_subdev_input_index(vpfe, &subdev, &index,
					inp->index) < 0) {
		vpfe_dbg(1, vpfe,
			"input information not found for the subdev\n");
		return -EINVAL;
	}
	sdinfo = &vpfe->cfg->sub_devs[subdev];
	*inp = sdinfo->inputs[index];

	return 0;
}