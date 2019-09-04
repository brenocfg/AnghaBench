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
struct mt9v111_dev {int /*<<< orphan*/  reset; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int __mt9v111_hw_reset(struct mt9v111_dev *mt9v111)
{
	if (!mt9v111->reset)
		return -EINVAL;

	gpiod_set_value(mt9v111->reset, 1);
	usleep_range(500, 1000);

	gpiod_set_value(mt9v111->reset, 0);
	usleep_range(500, 1000);

	return 0;
}