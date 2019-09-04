#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct sdio_func {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (TYPE_1__*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  sdio_func_present (struct sdio_func*) ; 

void sdio_remove_func(struct sdio_func *func)
{
	if (!sdio_func_present(func))
		return;

	device_del(&func->dev);
	of_node_put(func->dev.of_node);
	put_device(&func->dev);
}