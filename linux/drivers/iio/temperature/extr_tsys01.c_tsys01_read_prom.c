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
struct tsys01_dev {int (* read_prom_word ) (int /*<<< orphan*/ ,scalar_t__,int*) ;int* prom; int /*<<< orphan*/  client; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ TSYS01_PROM_READ ; 
 int TSYS01_PROM_WORDS_NB ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*) ; 
 struct tsys01_dev* iio_priv (struct iio_dev*) ; 
 int sprintf (char*,char*,int) ; 
 int stub1 (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  tsys01_crc_valid (int*) ; 

__attribute__((used)) static int tsys01_read_prom(struct iio_dev *indio_dev)
{
	int i, ret;
	struct tsys01_dev *dev_data = iio_priv(indio_dev);
	char buf[7 * TSYS01_PROM_WORDS_NB + 1];
	char *ptr = buf;

	for (i = 0; i < TSYS01_PROM_WORDS_NB; i++) {
		ret = dev_data->read_prom_word(dev_data->client,
					       TSYS01_PROM_READ + (i << 1),
					       &dev_data->prom[i]);
		if (ret)
			return ret;

		ret = sprintf(ptr, "0x%04x ", dev_data->prom[i]);
		ptr += ret;
	}

	if (!tsys01_crc_valid(dev_data->prom)) {
		dev_err(&indio_dev->dev, "prom crc check error\n");
		return -ENODEV;
	}
	*ptr = 0;
	dev_info(&indio_dev->dev, "PROM coefficients : %s\n", buf);

	return 0;
}