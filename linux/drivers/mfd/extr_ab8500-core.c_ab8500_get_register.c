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
typedef  int /*<<< orphan*/  u8 ;
struct device {int /*<<< orphan*/  parent; } ;
struct ab8500 {int /*<<< orphan*/  transfer_ongoing; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct ab8500* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int get_register_interruptible (struct ab8500*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ab8500_get_register(struct device *dev, u8 bank,
	u8 reg, u8 *value)
{
	int ret;
	struct ab8500 *ab8500 = dev_get_drvdata(dev->parent);

	atomic_inc(&ab8500->transfer_ongoing);
	ret = get_register_interruptible(ab8500, bank, reg, value);
	atomic_dec(&ab8500->transfer_ongoing);
	return ret;
}