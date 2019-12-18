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
typedef  int u32 ;
struct v4l2_capability {scalar_t__ bus_info; scalar_t__ card; scalar_t__ driver; } ;
struct file {int dummy; } ;
struct TYPE_2__ {char* name; } ;
struct bm2835_mmal_dev {TYPE_1__ v4l2_dev; int /*<<< orphan*/  instance; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  vchiq_mmal_version (int /*<<< orphan*/ ,int*,int*) ; 
 struct bm2835_mmal_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_querycap(struct file *file, void *priv,
			   struct v4l2_capability *cap)
{
	struct bm2835_mmal_dev *dev = video_drvdata(file);
	u32 major;
	u32 minor;

	vchiq_mmal_version(dev->instance, &major, &minor);

	strcpy((char *)cap->driver, "bm2835 mmal");
	snprintf((char *)cap->card, sizeof(cap->card), "mmal service %d.%d",
		 major, minor);

	snprintf((char *)cap->bus_info, sizeof(cap->bus_info),
		 "platform:%s", dev->v4l2_dev.name);
	return 0;
}