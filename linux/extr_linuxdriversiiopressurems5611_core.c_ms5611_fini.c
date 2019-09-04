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
struct ms5611_state {int /*<<< orphan*/  vdd; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 struct ms5611_state* iio_priv (struct iio_dev const*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ms5611_fini(const struct iio_dev *indio_dev)
{
	const struct ms5611_state *st = iio_priv(indio_dev);

	regulator_disable(st->vdd);
}