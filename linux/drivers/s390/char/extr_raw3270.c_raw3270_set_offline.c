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
struct raw3270 {int /*<<< orphan*/  flags; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  RAW3270_FLAGS_CONSOLE ; 
 struct raw3270* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw3270_remove (struct ccw_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
raw3270_set_offline (struct ccw_device *cdev)
{
	struct raw3270 *rp;

	rp = dev_get_drvdata(&cdev->dev);
	if (test_bit(RAW3270_FLAGS_CONSOLE, &rp->flags))
		return -EBUSY;
	raw3270_remove(cdev);
	return 0;
}