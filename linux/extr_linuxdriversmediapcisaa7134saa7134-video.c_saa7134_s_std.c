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
typedef  int v4l2_std_id ;
struct v4l2_fh {int dummy; } ;
struct saa7134_dev {int /*<<< orphan*/  slock; struct v4l2_fh* overlay_owner; } ;
struct file {int dummy; } ;
struct TYPE_3__ {int id; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 unsigned int TVNORMS ; 
 int V4L2_STD_SECAM ; 
 int V4L2_STD_SECAM_DK ; 
 int V4L2_STD_SECAM_L ; 
 int V4L2_STD_SECAM_LC ; 
 scalar_t__ is_empress (struct file*) ; 
 int /*<<< orphan*/  saa7134_tvaudio_do_scan (struct saa7134_dev*) ; 
 char* secam ; 
 int /*<<< orphan*/  set_tvnorm (struct saa7134_dev*,TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  start_preview (struct saa7134_dev*) ; 
 int /*<<< orphan*/  stop_preview (struct saa7134_dev*) ; 
 TYPE_1__* tvnorms ; 
 struct saa7134_dev* video_drvdata (struct file*) ; 

int saa7134_s_std(struct file *file, void *priv, v4l2_std_id id)
{
	struct saa7134_dev *dev = video_drvdata(file);
	struct v4l2_fh *fh = priv;
	unsigned long flags;
	unsigned int i;
	v4l2_std_id fixup;

	if (is_empress(file) && dev->overlay_owner) {
		/* Don't change the std from the mpeg device
		   if overlay is active. */
		return -EBUSY;
	}

	for (i = 0; i < TVNORMS; i++)
		if (id == tvnorms[i].id)
			break;

	if (i == TVNORMS)
		for (i = 0; i < TVNORMS; i++)
			if (id & tvnorms[i].id)
				break;
	if (i == TVNORMS)
		return -EINVAL;

	if ((id & V4L2_STD_SECAM) && (secam[0] != '-')) {
		if (secam[0] == 'L' || secam[0] == 'l') {
			if (secam[1] == 'C' || secam[1] == 'c')
				fixup = V4L2_STD_SECAM_LC;
			else
				fixup = V4L2_STD_SECAM_L;
		} else {
			if (secam[0] == 'D' || secam[0] == 'd')
				fixup = V4L2_STD_SECAM_DK;
			else
				fixup = V4L2_STD_SECAM;
		}
		for (i = 0; i < TVNORMS; i++) {
			if (fixup == tvnorms[i].id)
				break;
		}
		if (i == TVNORMS)
			return -EINVAL;
	}

	id = tvnorms[i].id;

	if (!is_empress(file) && fh == dev->overlay_owner) {
		spin_lock_irqsave(&dev->slock, flags);
		stop_preview(dev);
		spin_unlock_irqrestore(&dev->slock, flags);

		set_tvnorm(dev, &tvnorms[i]);

		spin_lock_irqsave(&dev->slock, flags);
		start_preview(dev);
		spin_unlock_irqrestore(&dev->slock, flags);
	} else
		set_tvnorm(dev, &tvnorms[i]);

	saa7134_tvaudio_do_scan(dev);
	return 0;
}