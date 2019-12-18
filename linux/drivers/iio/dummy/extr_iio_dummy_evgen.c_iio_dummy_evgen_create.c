#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  irq_sim; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IIO_EVENTGEN_NO ; 
 TYPE_1__* iio_evgen ; 
 int irq_sim_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_sim_irqnum (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iio_dummy_evgen_create(void)
{
	int ret;

	iio_evgen = kzalloc(sizeof(*iio_evgen), GFP_KERNEL);
	if (!iio_evgen)
		return -ENOMEM;

	ret = irq_sim_init(&iio_evgen->irq_sim, IIO_EVENTGEN_NO);
	if (ret < 0) {
		kfree(iio_evgen);
		return ret;
	}

	iio_evgen->base = irq_sim_irqnum(&iio_evgen->irq_sim, 0);
	mutex_init(&iio_evgen->lock);

	return 0;
}