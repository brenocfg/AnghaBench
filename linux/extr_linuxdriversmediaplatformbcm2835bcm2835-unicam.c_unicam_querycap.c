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
struct TYPE_2__ {char* name; } ;
struct unicam_device {TYPE_1__ v4l2_dev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNICAM_MODULE_NAME ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct unicam_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int unicam_querycap(struct file *file, void *priv,
			   struct v4l2_capability *cap)
{
	struct unicam_device *dev = video_drvdata(file);

	strlcpy(cap->driver, UNICAM_MODULE_NAME, sizeof(cap->driver));
	strlcpy(cap->card, UNICAM_MODULE_NAME, sizeof(cap->card));

	snprintf(cap->bus_info, sizeof(cap->bus_info),
		 "platform:%s", dev->v4l2_dev.name);

	return 0;
}