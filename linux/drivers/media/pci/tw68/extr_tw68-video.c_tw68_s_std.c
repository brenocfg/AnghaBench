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
struct tw68_dev {int /*<<< orphan*/  vidq; } ;
struct file {int dummy; } ;
struct TYPE_3__ {int id; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 unsigned int TVNORMS ; 
 int /*<<< orphan*/  set_tvnorm (struct tw68_dev*,TYPE_1__*) ; 
 TYPE_1__* tvnorms ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct tw68_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int tw68_s_std(struct file *file, void *priv, v4l2_std_id id)
{
	struct tw68_dev *dev = video_drvdata(file);
	unsigned int i;

	if (vb2_is_busy(&dev->vidq))
		return -EBUSY;

	/* Look for match on complete norm id (may have mult bits) */
	for (i = 0; i < TVNORMS; i++) {
		if (id == tvnorms[i].id)
			break;
	}

	/* If no exact match, look for norm which contains this one */
	if (i == TVNORMS) {
		for (i = 0; i < TVNORMS; i++)
			if (id & tvnorms[i].id)
				break;
	}
	/* If still not matched, give up */
	if (i == TVNORMS)
		return -EINVAL;

	set_tvnorm(dev, &tvnorms[i]);	/* do the actual setting */
	return 0;
}