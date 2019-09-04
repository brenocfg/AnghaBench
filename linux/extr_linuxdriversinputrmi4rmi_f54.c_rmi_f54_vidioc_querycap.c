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
struct v4l2_capability {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct file {int dummy; } ;
struct f54_data {TYPE_1__* fn; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  F54_NAME ; 
 int /*<<< orphan*/  SYNAPTICS_INPUT_DEVICE_NAME ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct f54_data* video_drvdata (struct file*) ; 

__attribute__((used)) static int rmi_f54_vidioc_querycap(struct file *file, void *priv,
				   struct v4l2_capability *cap)
{
	struct f54_data *f54 = video_drvdata(file);

	strlcpy(cap->driver, F54_NAME, sizeof(cap->driver));
	strlcpy(cap->card, SYNAPTICS_INPUT_DEVICE_NAME, sizeof(cap->card));
	snprintf(cap->bus_info, sizeof(cap->bus_info),
		"rmi4:%s", dev_name(&f54->fn->dev));

	return 0;
}