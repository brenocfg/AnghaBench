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
struct hwspinlock {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwspin_lock_free (struct hwspinlock*) ; 

__attribute__((used)) static void devm_hwspin_lock_release(struct device *dev, void *res)
{
	hwspin_lock_free(*(struct hwspinlock **)res);
}