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
struct rcar_drif_sdr {TYPE_1__* vdev; } ;
struct file {int dummy; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 char* KBUILD_MODNAME ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 struct rcar_drif_sdr* video_drvdata (struct file*) ; 

__attribute__((used)) static int rcar_drif_querycap(struct file *file, void *fh,
			      struct v4l2_capability *cap)
{
	struct rcar_drif_sdr *sdr = video_drvdata(file);

	strscpy(cap->driver, KBUILD_MODNAME, sizeof(cap->driver));
	strscpy(cap->card, sdr->vdev->name, sizeof(cap->card));
	snprintf(cap->bus_info, sizeof(cap->bus_info), "platform:%s",
		 sdr->vdev->name);

	return 0;
}