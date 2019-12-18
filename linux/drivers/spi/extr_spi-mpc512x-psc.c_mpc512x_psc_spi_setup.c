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
struct spi_device {int bits_per_word; int mode; int /*<<< orphan*/  max_speed_hz; struct mpc512x_psc_spi_cs* controller_state; int /*<<< orphan*/  cs_gpio; int /*<<< orphan*/  dev; } ;
struct mpc512x_psc_spi_cs {int bits_per_word; int /*<<< orphan*/  speed_hz; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SPI_CS_HIGH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mpc512x_psc_spi_cs*) ; 
 struct mpc512x_psc_spi_cs* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpc512x_psc_spi_setup(struct spi_device *spi)
{
	struct mpc512x_psc_spi_cs *cs = spi->controller_state;
	int ret;

	if (spi->bits_per_word % 8)
		return -EINVAL;

	if (!cs) {
		cs = kzalloc(sizeof *cs, GFP_KERNEL);
		if (!cs)
			return -ENOMEM;

		if (gpio_is_valid(spi->cs_gpio)) {
			ret = gpio_request(spi->cs_gpio, dev_name(&spi->dev));
			if (ret) {
				dev_err(&spi->dev, "can't get CS gpio: %d\n",
					ret);
				kfree(cs);
				return ret;
			}
			gpio_direction_output(spi->cs_gpio,
					spi->mode & SPI_CS_HIGH ? 0 : 1);
		}

		spi->controller_state = cs;
	}

	cs->bits_per_word = spi->bits_per_word;
	cs->speed_hz = spi->max_speed_hz;

	return 0;
}