#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct w5500_spi_priv {int dummy; } ;
struct w5200_spi_priv {int dummy; } ;
struct w5100_ops {int dummy; } ;
struct TYPE_4__ {scalar_t__ of_node; } ;
struct spi_device {int /*<<< orphan*/  irq; TYPE_1__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
typedef  int kernel_ulong_t ;
struct TYPE_5__ {int driver_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
#define  W5100 130 
#define  W5200 129 
#define  W5500 128 
 void* of_get_mac_address (scalar_t__) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_2__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  w5100_of_match ; 
 int w5100_probe (TYPE_1__*,struct w5100_ops const*,int,void const*,int /*<<< orphan*/ ,int) ; 
 struct w5100_ops w5100_spi_ops ; 
 struct w5100_ops w5200_ops ; 
 struct w5100_ops w5500_ops ; 

__attribute__((used)) static int w5100_spi_probe(struct spi_device *spi)
{
	const struct of_device_id *of_id;
	const struct w5100_ops *ops;
	kernel_ulong_t driver_data;
	int priv_size;
	const void *mac = of_get_mac_address(spi->dev.of_node);

	if (spi->dev.of_node) {
		of_id = of_match_device(w5100_of_match, &spi->dev);
		if (!of_id)
			return -ENODEV;
		driver_data = (kernel_ulong_t)of_id->data;
	} else {
		driver_data = spi_get_device_id(spi)->driver_data;
	}

	switch (driver_data) {
	case W5100:
		ops = &w5100_spi_ops;
		priv_size = 0;
		break;
	case W5200:
		ops = &w5200_ops;
		priv_size = sizeof(struct w5200_spi_priv);
		break;
	case W5500:
		ops = &w5500_ops;
		priv_size = sizeof(struct w5500_spi_priv);
		break;
	default:
		return -EINVAL;
	}

	return w5100_probe(&spi->dev, ops, priv_size, mac, spi->irq, -EINVAL);
}