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
struct mcam_camera {int dummy; } ;
struct mmp_camera {struct mcam_camera mcam; } ;

/* Variables and functions */
 int /*<<< orphan*/  mccic_shutdown (struct mcam_camera*) ; 
 int /*<<< orphan*/  mmpcam_remove_device (struct mmp_camera*) ; 

__attribute__((used)) static int mmpcam_remove(struct mmp_camera *cam)
{
	struct mcam_camera *mcam = &cam->mcam;

	mmpcam_remove_device(cam);
	mccic_shutdown(mcam);
	return 0;
}