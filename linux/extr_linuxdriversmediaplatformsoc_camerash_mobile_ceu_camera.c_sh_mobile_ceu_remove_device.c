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
struct soc_camera_device {int /*<<< orphan*/  devnum; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_mobile_ceu_remove_device(struct soc_camera_device *icd)
{
	dev_info(icd->parent,
		 "SuperH Mobile CEU driver detached from camera %d\n",
		 icd->devnum);
}