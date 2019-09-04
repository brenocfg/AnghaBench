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
struct sdio_func {int /*<<< orphan*/  dev; int /*<<< orphan*/  num; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_set_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_enable_async_suspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_card_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_acpi_set_handle (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_func_set_present (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_set_of_node (struct sdio_func*) ; 

int sdio_add_func(struct sdio_func *func)
{
	int ret;

	dev_set_name(&func->dev, "%s:%d", mmc_card_id(func->card), func->num);

	sdio_set_of_node(func);
	sdio_acpi_set_handle(func);
	device_enable_async_suspend(&func->dev);
	ret = device_add(&func->dev);
	if (ret == 0)
		sdio_func_set_present(func);

	return ret;
}