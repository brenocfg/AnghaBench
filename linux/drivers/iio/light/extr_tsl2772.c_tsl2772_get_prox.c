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
struct tsl2772_chip {int id; int prox_data; int /*<<< orphan*/  prox_mutex; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TSL2772_PRX_HI ; 
 int /*<<< orphan*/  TSL2772_PRX_LO ; 
 int TSL2772_STA_ADC_VALID ; 
 int TSL2772_STA_PRX_VALID ; 
#define  apds9930 138 
 struct tsl2772_chip* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
#define  tmd2671 137 
#define  tmd2672 136 
#define  tmd2771 135 
#define  tmd2772 134 
#define  tsl2571 133 
#define  tsl2572 132 
#define  tsl2671 131 
#define  tsl2672 130 
#define  tsl2771 129 
#define  tsl2772 128 
 int tsl2772_read_autoinc_regs (struct tsl2772_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tsl2772_read_status (struct tsl2772_chip*) ; 

__attribute__((used)) static int tsl2772_get_prox(struct iio_dev *indio_dev)
{
	struct tsl2772_chip *chip = iio_priv(indio_dev);
	int ret;

	mutex_lock(&chip->prox_mutex);

	ret = tsl2772_read_status(chip);
	if (ret < 0)
		goto prox_poll_err;

	switch (chip->id) {
	case tsl2571:
	case tsl2671:
	case tmd2671:
	case tsl2771:
	case tmd2771:
		if (!(ret & TSL2772_STA_ADC_VALID)) {
			ret = -EINVAL;
			goto prox_poll_err;
		}
		break;
	case tsl2572:
	case tsl2672:
	case tmd2672:
	case tsl2772:
	case tmd2772:
	case apds9930:
		if (!(ret & TSL2772_STA_PRX_VALID)) {
			ret = -EINVAL;
			goto prox_poll_err;
		}
		break;
	}

	ret = tsl2772_read_autoinc_regs(chip, TSL2772_PRX_LO, TSL2772_PRX_HI);
	if (ret < 0)
		goto prox_poll_err;
	chip->prox_data = ret;

prox_poll_err:
	mutex_unlock(&chip->prox_mutex);

	return ret;
}