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
struct device {int /*<<< orphan*/  parent; } ;
struct ab8500 {scalar_t__ chip_id; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ab8500* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ab8500_get_chip_id(struct device *dev)
{
	struct ab8500 *ab8500;

	if (!dev)
		return -EINVAL;
	ab8500 = dev_get_drvdata(dev->parent);
	return ab8500 ? (int)ab8500->chip_id : -EINVAL;
}