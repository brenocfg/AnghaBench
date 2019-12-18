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
struct omap_vout_device {int vid; TYPE_1__* vfd; } ;
struct file {int dummy; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 char* VOUT_NAME ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 struct omap_vout_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_querycap(struct file *file, void *fh,
		struct v4l2_capability *cap)
{
	struct omap_vout_device *vout = video_drvdata(file);

	strscpy(cap->driver, VOUT_NAME, sizeof(cap->driver));
	strscpy(cap->card, vout->vfd->name, sizeof(cap->card));
	snprintf(cap->bus_info, sizeof(cap->bus_info),
		 "platform:%s.%d", VOUT_NAME, vout->vid);
	return 0;
}