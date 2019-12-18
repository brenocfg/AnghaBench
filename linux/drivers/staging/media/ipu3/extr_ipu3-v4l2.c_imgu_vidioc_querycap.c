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
struct v4l2_capability {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct imgu_video_device {char* name; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMGU_NAME ; 
 struct imgu_video_device* file_to_intel_imgu_node (struct file*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int imgu_vidioc_querycap(struct file *file, void *fh,
				struct v4l2_capability *cap)
{
	struct imgu_video_device *node = file_to_intel_imgu_node(file);

	strscpy(cap->driver, IMGU_NAME, sizeof(cap->driver));
	strscpy(cap->card, IMGU_NAME, sizeof(cap->card));
	snprintf(cap->bus_info, sizeof(cap->bus_info), "PCI:%s", node->name);

	return 0;
}