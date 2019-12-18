#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sdio_func {scalar_t__ vendor; TYPE_2__* card; int /*<<< orphan*/  device; } ;
struct TYPE_3__ {scalar_t__ vendor; int /*<<< orphan*/  device; } ;
struct TYPE_4__ {TYPE_1__ cis; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int sdio_read_cis (TYPE_2__*,struct sdio_func*) ; 

int sdio_read_func_cis(struct sdio_func *func)
{
	int ret;

	ret = sdio_read_cis(func->card, func);
	if (ret)
		return ret;

	/*
	 * Since we've linked to tuples in the card structure,
	 * we must make sure we have a reference to it.
	 */
	get_device(&func->card->dev);

	/*
	 * Vendor/device id is optional for function CIS, so
	 * copy it from the card structure as needed.
	 */
	if (func->vendor == 0) {
		func->vendor = func->card->cis.vendor;
		func->device = func->card->cis.device;
	}

	return 0;
}