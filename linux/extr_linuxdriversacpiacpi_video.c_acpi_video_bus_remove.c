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
struct acpi_video_bus {struct acpi_video_bus* attached_array; int /*<<< orphan*/  entry; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct acpi_video_bus* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_video_bus_put_devices (struct acpi_video_bus*) ; 
 int /*<<< orphan*/  acpi_video_bus_remove_notify_handler (struct acpi_video_bus*) ; 
 int /*<<< orphan*/  acpi_video_bus_unregister_backlight (struct acpi_video_bus*) ; 
 int /*<<< orphan*/  kfree (struct acpi_video_bus*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_list_lock ; 

__attribute__((used)) static int acpi_video_bus_remove(struct acpi_device *device)
{
	struct acpi_video_bus *video = NULL;


	if (!device || !acpi_driver_data(device))
		return -EINVAL;

	video = acpi_driver_data(device);

	acpi_video_bus_remove_notify_handler(video);
	acpi_video_bus_unregister_backlight(video);
	acpi_video_bus_put_devices(video);

	mutex_lock(&video_list_lock);
	list_del(&video->entry);
	mutex_unlock(&video_list_lock);

	kfree(video->attached_array);
	kfree(video);

	return 0;
}