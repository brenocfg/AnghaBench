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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct vpfe_subdev_info {TYPE_1__* inputs; } ;
struct vpfe_device {size_t std_index; struct vpfe_subdev_info* current_subdev; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  std_id; } ;
struct TYPE_3__ {scalar_t__ capabilities; } ;

/* Variables and functions */
 int ENODATA ; 
 scalar_t__ V4L2_IN_CAP_STD ; 
 struct vpfe_device* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vpfe_dbg (int,struct vpfe_device*,char*) ; 
 TYPE_2__* vpfe_standards ; 

__attribute__((used)) static int vpfe_g_std(struct file *file, void *priv, v4l2_std_id *std_id)
{
	struct vpfe_device *vpfe = video_drvdata(file);
	struct vpfe_subdev_info *sdinfo;

	vpfe_dbg(2, vpfe, "vpfe_g_std\n");

	sdinfo = vpfe->current_subdev;
	if (sdinfo->inputs[0].capabilities != V4L2_IN_CAP_STD)
		return -ENODATA;

	*std_id = vpfe_standards[vpfe->std_index].std_id;

	return 0;
}