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
typedef  int uint8_t ;
struct max1111_data {int* tx_buf; int sel_sh; int* rx_buf; int /*<<< orphan*/  drvdata_lock; int /*<<< orphan*/  msg; int /*<<< orphan*/  spi; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX1111_CTRL_PD0 ; 
 int MAX1111_CTRL_PD1 ; 
 int MAX1111_CTRL_SGL ; 
 int MAX1111_CTRL_STR ; 
 int MAX1111_CTRL_UNI ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct max1111_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int spi_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int max1111_read(struct device *dev, int channel)
{
	struct max1111_data *data = dev_get_drvdata(dev);
	uint8_t v1, v2;
	int err;

	/* writing to drvdata struct is not thread safe, wait on mutex */
	mutex_lock(&data->drvdata_lock);

	data->tx_buf[0] = (channel << data->sel_sh) |
		MAX1111_CTRL_PD0 | MAX1111_CTRL_PD1 |
		MAX1111_CTRL_SGL | MAX1111_CTRL_UNI | MAX1111_CTRL_STR;

	err = spi_sync(data->spi, &data->msg);
	if (err < 0) {
		dev_err(dev, "spi_sync failed with %d\n", err);
		mutex_unlock(&data->drvdata_lock);
		return err;
	}

	v1 = data->rx_buf[0];
	v2 = data->rx_buf[1];

	mutex_unlock(&data->drvdata_lock);

	if ((v1 & 0xc0) || (v2 & 0x3f))
		return -EINVAL;

	return (v1 << 2) | (v2 >> 6);
}