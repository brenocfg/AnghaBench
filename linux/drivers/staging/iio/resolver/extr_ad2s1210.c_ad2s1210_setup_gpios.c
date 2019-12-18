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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct ad2s1210_state {int /*<<< orphan*/ * gpios; struct spi_device* sdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  devm_gpiod_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* gpios ; 

__attribute__((used)) static int ad2s1210_setup_gpios(struct ad2s1210_state *st)
{
	struct spi_device *spi = st->sdev;
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(gpios); i++) {
		st->gpios[i] = devm_gpiod_get(&spi->dev, gpios[i].name,
					      gpios[i].flags);
		if (IS_ERR(st->gpios[i])) {
			ret = PTR_ERR(st->gpios[i]);
			dev_err(&spi->dev,
				"ad2s1210: failed to request %s GPIO: %d\n",
				gpios[i].name, ret);
			return ret;
		}
	}

	return 0;
}