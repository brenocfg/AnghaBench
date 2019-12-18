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
struct reset_controller_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  reset_controller_unregister (struct reset_controller_dev*) ; 

__attribute__((used)) static void devm_reset_controller_release(struct device *dev, void *res)
{
	reset_controller_unregister(*(struct reset_controller_dev **)res);
}