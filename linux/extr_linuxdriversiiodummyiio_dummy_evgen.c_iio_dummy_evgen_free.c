#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  irq_sim; } ;

/* Variables and functions */
 TYPE_1__* iio_evgen ; 
 int /*<<< orphan*/  irq_sim_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static void iio_dummy_evgen_free(void)
{
	irq_sim_fini(&iio_evgen->irq_sim);
	kfree(iio_evgen);
}