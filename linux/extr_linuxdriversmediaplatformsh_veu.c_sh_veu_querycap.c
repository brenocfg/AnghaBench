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
struct v4l2_capability {int device_caps; int capabilities; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_M2M ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int sh_veu_querycap(struct file *file, void *priv,
			   struct v4l2_capability *cap)
{
	strlcpy(cap->driver, "sh-veu", sizeof(cap->driver));
	strlcpy(cap->card, "sh-mobile VEU", sizeof(cap->card));
	strlcpy(cap->bus_info, "platform:sh-veu", sizeof(cap->bus_info));
	cap->device_caps = V4L2_CAP_VIDEO_M2M | V4L2_CAP_STREAMING;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;

	return 0;
}