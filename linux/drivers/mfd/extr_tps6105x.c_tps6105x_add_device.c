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
struct tps6105x {TYPE_1__* client; } ;
struct mfd_cell {int pdata_size; struct tps6105x* platform_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int mfd_add_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mfd_cell*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tps6105x_add_device(struct tps6105x *tps6105x,
			       struct mfd_cell *cell)
{
	cell->platform_data = tps6105x;
	cell->pdata_size = sizeof(*tps6105x);

	return mfd_add_devices(&tps6105x->client->dev,
			       PLATFORM_DEVID_AUTO, cell, 1, NULL, 0, NULL);
}