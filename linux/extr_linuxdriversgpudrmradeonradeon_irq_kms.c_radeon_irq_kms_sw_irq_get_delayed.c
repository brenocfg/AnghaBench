#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * ring_int; } ;
struct radeon_device {TYPE_1__ irq; } ;

/* Variables and functions */
 int atomic_inc_return (int /*<<< orphan*/ *) ; 

bool radeon_irq_kms_sw_irq_get_delayed(struct radeon_device *rdev, int ring)
{
	return atomic_inc_return(&rdev->irq.ring_int[ring]) == 1;
}