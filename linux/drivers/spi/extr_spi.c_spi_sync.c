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
struct spi_message {int dummy; } ;
struct spi_device {TYPE_1__* controller; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus_lock_mutex; } ;

/* Variables and functions */
 int __spi_sync (struct spi_device*,struct spi_message*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int spi_sync(struct spi_device *spi, struct spi_message *message)
{
	int ret;

	mutex_lock(&spi->controller->bus_lock_mutex);
	ret = __spi_sync(spi, message);
	mutex_unlock(&spi->controller->bus_lock_mutex);

	return ret;
}