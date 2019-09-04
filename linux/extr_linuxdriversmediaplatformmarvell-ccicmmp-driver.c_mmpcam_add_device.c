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
struct mmp_camera {int /*<<< orphan*/  devlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmpcam_devices ; 
 int /*<<< orphan*/  mmpcam_devices_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mmpcam_add_device(struct mmp_camera *cam)
{
	mutex_lock(&mmpcam_devices_lock);
	list_add(&cam->devlist, &mmpcam_devices);
	mutex_unlock(&mmpcam_devices_lock);
}