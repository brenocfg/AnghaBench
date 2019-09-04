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
struct vpif_capture_config {int /*<<< orphan*/  card_name; } ;
struct v4l2_capability {int device_caps; int capabilities; int /*<<< orphan*/  card; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  driver; } ;
struct file {int dummy; } ;
struct TYPE_3__ {struct vpif_capture_config* platform_data; } ;

/* Variables and functions */
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  VPIF_DRIVER_NAME ; 
 char* dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* vpif_dev ; 

__attribute__((used)) static int vpif_querycap(struct file *file, void  *priv,
				struct v4l2_capability *cap)
{
	struct vpif_capture_config *config = vpif_dev->platform_data;

	cap->device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;
	strlcpy(cap->driver, VPIF_DRIVER_NAME, sizeof(cap->driver));
	snprintf(cap->bus_info, sizeof(cap->bus_info), "platform:%s",
		 dev_name(vpif_dev));
	strlcpy(cap->card, config->card_name, sizeof(cap->card));

	return 0;
}