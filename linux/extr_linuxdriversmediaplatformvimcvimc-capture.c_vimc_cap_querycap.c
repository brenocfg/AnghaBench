#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* v4l2_dev; } ;
struct vimc_cap_device {TYPE_2__ vdev; } ;
struct v4l2_capability {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct file {int dummy; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct vimc_cap_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vimc_cap_querycap(struct file *file, void *priv,
			     struct v4l2_capability *cap)
{
	struct vimc_cap_device *vcap = video_drvdata(file);

	strlcpy(cap->driver, KBUILD_MODNAME, sizeof(cap->driver));
	strlcpy(cap->card, KBUILD_MODNAME, sizeof(cap->card));
	snprintf(cap->bus_info, sizeof(cap->bus_info),
		 "platform:%s", vcap->vdev.v4l2_dev->name);

	return 0;
}