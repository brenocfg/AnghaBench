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
 int mask_and_set_register_interruptible (struct ab8500*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ab8500_mask_and_set_register(struct device *dev,
	u8 bank, u8 reg, u8 bitmask, u8 bitvalues)
{
	int ret;
	struct ab8500 *ab8500 = dev_get_drvdata(dev->parent);

	atomic_inc(&ab8500->transfer_ongoing);
	ret = mask_and_set_register_interruptible(ab8500, bank, reg,
						 bitmask, bitvalues);
	atomic_dec(&ab8500->transfer_ongoing);
	return ret;
}