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
struct iio_dummy_regs {int dummy; } ;
struct TYPE_2__ {int base; struct iio_dummy_regs* regs; } ;

/* Variables and functions */
 TYPE_1__* iio_evgen ; 

struct iio_dummy_regs *iio_dummy_evgen_get_regs(int irq)
{
	return &iio_evgen->regs[irq - iio_evgen->base];
}