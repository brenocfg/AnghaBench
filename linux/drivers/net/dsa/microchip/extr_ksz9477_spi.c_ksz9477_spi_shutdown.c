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
struct spi_device {int dummy; } ;
struct ksz_device {TYPE_1__* dev_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* shutdown ) (struct ksz_device*) ;} ;

/* Variables and functions */
 struct ksz_device* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  stub1 (struct ksz_device*) ; 

__attribute__((used)) static void ksz9477_spi_shutdown(struct spi_device *spi)
{
	struct ksz_device *dev = spi_get_drvdata(spi);

	if (dev && dev->dev_ops->shutdown)
		dev->dev_ops->shutdown(dev);
}