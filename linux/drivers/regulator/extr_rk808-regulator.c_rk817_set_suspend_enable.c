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
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int rk817_set_suspend_enable_ctrl (struct regulator_dev*,int) ; 

__attribute__((used)) static int rk817_set_suspend_enable(struct regulator_dev *rdev)
{
	return rk817_set_suspend_enable_ctrl(rdev, 1);
}