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
struct s2255_pipeinfo {int dummy; } ;
struct s2255_dev {scalar_t__ cc; TYPE_1__* udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ MAX_CHANNELS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dprintk (struct s2255_dev*,int,char*) ; 
 int save_frame (struct s2255_dev*,struct s2255_pipeinfo*) ; 

__attribute__((used)) static void s2255_read_video_callback(struct s2255_dev *dev,
				      struct s2255_pipeinfo *pipe_info)
{
	int res;
	dprintk(dev, 50, "callback read video\n");

	if (dev->cc >= MAX_CHANNELS) {
		dev->cc = 0;
		dev_err(&dev->udev->dev, "invalid channel\n");
		return;
	}
	/* otherwise copy to the system buffers */
	res = save_frame(dev, pipe_info);
	if (res != 0)
		dprintk(dev, 4, "s2255: read callback failed\n");

	dprintk(dev, 50, "callback read video done\n");
	return;
}