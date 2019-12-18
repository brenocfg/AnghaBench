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
struct video_device {int dummy; } ;
struct file {struct bttv_fh* private_data; } ;
struct bttv_fh {int /*<<< orphan*/  fh; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr; } ;
struct bttv {int /*<<< orphan*/  mute; int /*<<< orphan*/  radio_user; struct bttv_fh init; TYPE_1__ c; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  audio_mute (struct bttv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 struct bttv_fh* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  v4l2_fh_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_init (int /*<<< orphan*/ *,struct video_device*) ; 
 struct video_device* video_devdata (struct file*) ; 
 int /*<<< orphan*/  video_device_node_name (struct video_device*) ; 
 struct bttv* video_drvdata (struct file*) ; 

__attribute__((used)) static int radio_open(struct file *file)
{
	struct video_device *vdev = video_devdata(file);
	struct bttv *btv = video_drvdata(file);
	struct bttv_fh *fh;

	dprintk("open dev=%s\n", video_device_node_name(vdev));

	dprintk("%d: open called (radio)\n", btv->c.nr);

	/* allocate per filehandle data */
	fh = kmalloc(sizeof(*fh), GFP_KERNEL);
	if (unlikely(!fh))
		return -ENOMEM;
	file->private_data = fh;
	*fh = btv->init;
	v4l2_fh_init(&fh->fh, vdev);

	btv->radio_user++;
	audio_mute(btv, btv->mute);

	v4l2_fh_add(&fh->fh);

	return 0;
}