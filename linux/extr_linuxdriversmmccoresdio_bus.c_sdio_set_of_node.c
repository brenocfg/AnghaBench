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
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct sdio_func {int /*<<< orphan*/  num; TYPE_2__ dev; TYPE_1__* card; } ;
struct mmc_host {int dummy; } ;
struct TYPE_3__ {struct mmc_host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_of_find_child_device (struct mmc_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdio_set_of_node(struct sdio_func *func)
{
	struct mmc_host *host = func->card->host;

	func->dev.of_node = mmc_of_find_child_device(host, func->num);
}