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
struct maple_device {int dummy; } ;
struct device {int dummy; } ;
struct dc_kbd {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dc_kbd*) ; 
 struct dc_kbd* maple_get_drvdata (struct maple_device*) ; 
 int /*<<< orphan*/  maple_keyb_mutex ; 
 int /*<<< orphan*/  maple_set_drvdata (struct maple_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct maple_device* to_maple_dev (struct device*) ; 

__attribute__((used)) static int remove_maple_kbd(struct device *dev)
{
	struct maple_device *mdev = to_maple_dev(dev);
	struct dc_kbd *kbd = maple_get_drvdata(mdev);

	mutex_lock(&maple_keyb_mutex);

	input_unregister_device(kbd->dev);
	kfree(kbd);

	maple_set_drvdata(mdev, NULL);

	mutex_unlock(&maple_keyb_mutex);
	return 0;
}