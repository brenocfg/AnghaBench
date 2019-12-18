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
struct video_device {int device_caps; int /*<<< orphan*/  num; int /*<<< orphan*/  name; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/  vfl_dir; int /*<<< orphan*/ * v4l2_dev; int /*<<< orphan*/ * lock; int /*<<< orphan*/  release; int /*<<< orphan*/ * fops; } ;
struct of_device_id {char* compatible; } ;
struct hantro_func {unsigned int id; struct video_device vdev; } ;
struct hantro_dev {int /*<<< orphan*/  v4l2_dev; struct hantro_func* decoder; struct hantro_func* encoder; int /*<<< orphan*/  vpu_mutex; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int MEDIA_ENT_F_PROC_VIDEO_ENCODER ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_M2M_MPLANE ; 
 int /*<<< orphan*/  VFL_DIR_M2M ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 struct hantro_func* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int hantro_attach_func (struct hantro_dev*,struct hantro_func*) ; 
 int /*<<< orphan*/  hantro_fops ; 
 int /*<<< orphan*/  hantro_ioctl_ops ; 
 int /*<<< orphan*/  of_hantro_match ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_device_release_empty ; 
 int video_register_device (struct video_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct hantro_dev*) ; 
 int /*<<< orphan*/  video_unregister_device (struct video_device*) ; 

__attribute__((used)) static int hantro_add_func(struct hantro_dev *vpu, unsigned int funcid)
{
	const struct of_device_id *match;
	struct hantro_func *func;
	struct video_device *vfd;
	int ret;

	match = of_match_node(of_hantro_match, vpu->dev->of_node);
	func = devm_kzalloc(vpu->dev, sizeof(*func), GFP_KERNEL);
	if (!func) {
		v4l2_err(&vpu->v4l2_dev, "Failed to allocate video device\n");
		return -ENOMEM;
	}

	func->id = funcid;

	vfd = &func->vdev;
	vfd->fops = &hantro_fops;
	vfd->release = video_device_release_empty;
	vfd->lock = &vpu->vpu_mutex;
	vfd->v4l2_dev = &vpu->v4l2_dev;
	vfd->vfl_dir = VFL_DIR_M2M;
	vfd->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_M2M_MPLANE;
	vfd->ioctl_ops = &hantro_ioctl_ops;
	snprintf(vfd->name, sizeof(vfd->name), "%s-%s", match->compatible,
		 funcid == MEDIA_ENT_F_PROC_VIDEO_ENCODER ? "enc" : "dec");

	if (funcid == MEDIA_ENT_F_PROC_VIDEO_ENCODER)
		vpu->encoder = func;
	else
		vpu->decoder = func;

	video_set_drvdata(vfd, vpu);

	ret = video_register_device(vfd, VFL_TYPE_GRABBER, -1);
	if (ret) {
		v4l2_err(&vpu->v4l2_dev, "Failed to register video device\n");
		return ret;
	}

	ret = hantro_attach_func(vpu, func);
	if (ret) {
		v4l2_err(&vpu->v4l2_dev,
			 "Failed to attach functionality to the media device\n");
		goto err_unreg_dev;
	}

	v4l2_info(&vpu->v4l2_dev, "registered %s as /dev/video%d\n", vfd->name,
		  vfd->num);

	return 0;

err_unreg_dev:
	video_unregister_device(vfd);
	return ret;
}