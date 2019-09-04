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
struct rmi_function {int /*<<< orphan*/  dev; } ;
struct f54_data {int /*<<< orphan*/  v4l2; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 struct f54_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rmi_f54_remove(struct rmi_function *fn)
{
	struct f54_data *f54 = dev_get_drvdata(&fn->dev);

	video_unregister_device(&f54->vdev);
	v4l2_device_unregister(&f54->v4l2);
}