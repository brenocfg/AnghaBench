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
struct tm6000_fh {struct tm6000_core* dev; } ;
struct tm6000_core {unsigned int input; int /*<<< orphan*/  norm; TYPE_1__* vinput; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
 int vidioc_s_std (struct file*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_s_input(struct file *file, void *priv, unsigned int i)
{
	struct tm6000_fh   *fh = priv;
	struct tm6000_core *dev = fh->dev;
	int rc = 0;

	if (i >= 3)
		return -EINVAL;
	if (!dev->vinput[i].type)
		return -EINVAL;

	dev->input = i;

	rc = vidioc_s_std(file, priv, dev->norm);

	return rc;
}