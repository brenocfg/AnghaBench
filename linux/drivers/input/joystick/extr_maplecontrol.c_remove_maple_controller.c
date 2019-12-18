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
struct maple_device {int /*<<< orphan*/ * callback; } ;
struct device {int dummy; } ;
struct dc_pad {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dc_pad*) ; 
 struct dc_pad* maple_get_drvdata (struct maple_device*) ; 
 int /*<<< orphan*/  maple_set_drvdata (struct maple_device*,int /*<<< orphan*/ *) ; 
 struct maple_device* to_maple_dev (struct device*) ; 

__attribute__((used)) static int remove_maple_controller(struct device *dev)
{
	struct maple_device *mdev = to_maple_dev(dev);
	struct dc_pad *pad = maple_get_drvdata(mdev);

	mdev->callback = NULL;
	input_unregister_device(pad->dev);
	maple_set_drvdata(mdev, NULL);
	kfree(pad);

	return 0;
}