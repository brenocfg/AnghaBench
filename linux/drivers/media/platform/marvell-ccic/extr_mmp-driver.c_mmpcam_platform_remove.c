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
struct platform_device {int dummy; } ;
struct mmp_camera {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 struct mmp_camera* mmpcam_find_device (struct platform_device*) ; 
 int mmpcam_remove (struct mmp_camera*) ; 

__attribute__((used)) static int mmpcam_platform_remove(struct platform_device *pdev)
{
	struct mmp_camera *cam = mmpcam_find_device(pdev);

	if (cam == NULL)
		return -ENODEV;
	return mmpcam_remove(cam);
}