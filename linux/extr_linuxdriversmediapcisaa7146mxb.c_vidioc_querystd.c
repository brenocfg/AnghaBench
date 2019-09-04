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
struct saa7146_fh {struct saa7146_dev* dev; } ;
struct saa7146_dev {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int call_all (struct saa7146_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  querystd ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int vidioc_querystd(struct file *file, void *fh, v4l2_std_id *norm)
{
	struct saa7146_dev *dev = ((struct saa7146_fh *)fh)->dev;

	return call_all(dev, video, querystd, norm);
}