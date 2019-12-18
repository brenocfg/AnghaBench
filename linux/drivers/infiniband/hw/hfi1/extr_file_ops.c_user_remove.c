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
struct hfi1_devdata {int /*<<< orphan*/  user_device; int /*<<< orphan*/  user_cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hfi1_cdev_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void user_remove(struct hfi1_devdata *dd)
{

	hfi1_cdev_cleanup(&dd->user_cdev, &dd->user_device);
}