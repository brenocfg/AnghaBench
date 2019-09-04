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
struct v4l2_capability {int device_caps; int capabilities; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct TYPE_2__ {char* name; } ;
struct pcm20 {TYPE_1__ v4l2_dev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_RADIO ; 
 int V4L2_CAP_RDS_CAPTURE ; 
 int V4L2_CAP_TUNER ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 struct pcm20* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_querycap(struct file *file, void *priv,
				struct v4l2_capability *v)
{
	struct pcm20 *dev = video_drvdata(file);

	strlcpy(v->driver, "Miro PCM20", sizeof(v->driver));
	strlcpy(v->card, "Miro PCM20", sizeof(v->card));
	snprintf(v->bus_info, sizeof(v->bus_info), "ISA:%s", dev->v4l2_dev.name);
	v->device_caps = V4L2_CAP_TUNER | V4L2_CAP_RADIO | V4L2_CAP_RDS_CAPTURE;
	v->capabilities = v->device_caps | V4L2_CAP_DEVICE_CAPS;
	return 0;
}