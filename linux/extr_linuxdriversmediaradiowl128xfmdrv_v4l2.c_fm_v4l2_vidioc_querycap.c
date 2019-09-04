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
 int /*<<< orphan*/  FM_DRV_CARD_SHORT_NAME ; 
 int /*<<< orphan*/  FM_DRV_NAME ; 
 int V4L2_CAP_AUDIO ; 
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_HW_FREQ_SEEK ; 
 int V4L2_CAP_MODULATOR ; 
 int V4L2_CAP_RADIO ; 
 int V4L2_CAP_RDS_CAPTURE ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_TUNER ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fm_v4l2_vidioc_querycap(struct file *file, void *priv,
		struct v4l2_capability *capability)
{
	strlcpy(capability->driver, FM_DRV_NAME, sizeof(capability->driver));
	strlcpy(capability->card, FM_DRV_CARD_SHORT_NAME,
			sizeof(capability->card));
	sprintf(capability->bus_info, "UART");
	capability->device_caps = V4L2_CAP_HW_FREQ_SEEK | V4L2_CAP_TUNER |
		V4L2_CAP_RADIO | V4L2_CAP_MODULATOR |
		V4L2_CAP_AUDIO | V4L2_CAP_READWRITE |
		V4L2_CAP_RDS_CAPTURE;
	capability->capabilities = capability->device_caps |
		V4L2_CAP_DEVICE_CAPS;

	return 0;
}