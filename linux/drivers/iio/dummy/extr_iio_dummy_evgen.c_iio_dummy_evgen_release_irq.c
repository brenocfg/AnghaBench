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
struct TYPE_2__ {int* inuse; int base; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 TYPE_1__* iio_evgen ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void iio_dummy_evgen_release_irq(int irq)
{
	mutex_lock(&iio_evgen->lock);
	iio_evgen->inuse[irq - iio_evgen->base] = false;
	mutex_unlock(&iio_evgen->lock);
}