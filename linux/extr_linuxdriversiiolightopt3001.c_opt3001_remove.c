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
typedef  int u16 ;
struct opt3001 {int /*<<< orphan*/  dev; int /*<<< orphan*/  client; scalar_t__ use_irq; } ;
struct iio_dev {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPT3001_CONFIGURATION ; 
 int /*<<< orphan*/  OPT3001_CONFIGURATION_M_SHUTDOWN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct iio_dev*) ; 
 struct iio_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_word_swapped (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_word_swapped (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct opt3001* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  opt3001_set_mode (struct opt3001*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int opt3001_remove(struct i2c_client *client)
{
	struct iio_dev *iio = i2c_get_clientdata(client);
	struct opt3001 *opt = iio_priv(iio);
	int ret;
	u16 reg;

	if (opt->use_irq)
		free_irq(client->irq, iio);

	ret = i2c_smbus_read_word_swapped(opt->client, OPT3001_CONFIGURATION);
	if (ret < 0) {
		dev_err(opt->dev, "failed to read register %02x\n",
				OPT3001_CONFIGURATION);
		return ret;
	}

	reg = ret;
	opt3001_set_mode(opt, &reg, OPT3001_CONFIGURATION_M_SHUTDOWN);

	ret = i2c_smbus_write_word_swapped(opt->client, OPT3001_CONFIGURATION,
			reg);
	if (ret < 0) {
		dev_err(opt->dev, "failed to write register %02x\n",
				OPT3001_CONFIGURATION);
		return ret;
	}

	return 0;
}