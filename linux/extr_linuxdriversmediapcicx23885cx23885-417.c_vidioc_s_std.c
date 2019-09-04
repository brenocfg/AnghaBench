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
struct file {int dummy; } ;
struct TYPE_3__ {int id; } ;
struct cx23885_dev {TYPE_1__ encodernorm; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int cx23885_set_tvnorm (struct cx23885_dev*,int) ; 
 TYPE_1__* cx23885_tvnorms ; 
 struct cx23885_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_std(struct file *file, void *priv, v4l2_std_id id)
{
	struct cx23885_dev *dev = video_drvdata(file);
	unsigned int i;
	int ret;

	for (i = 0; i < ARRAY_SIZE(cx23885_tvnorms); i++)
		if (id & cx23885_tvnorms[i].id)
			break;
	if (i == ARRAY_SIZE(cx23885_tvnorms))
		return -EINVAL;

	ret = cx23885_set_tvnorm(dev, id);
	if (!ret)
		dev->encodernorm = cx23885_tvnorms[i];
	return ret;
}