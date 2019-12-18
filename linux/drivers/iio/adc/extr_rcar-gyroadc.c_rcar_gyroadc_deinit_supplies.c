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
struct rcar_gyroadc {unsigned int num_channels; int /*<<< orphan*/ * vref; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 struct rcar_gyroadc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcar_gyroadc_deinit_supplies(struct iio_dev *indio_dev)
{
	struct rcar_gyroadc *priv = iio_priv(indio_dev);
	unsigned int i;

	for (i = 0; i < priv->num_channels; i++) {
		if (!priv->vref[i])
			continue;

		regulator_disable(priv->vref[i]);
	}
}