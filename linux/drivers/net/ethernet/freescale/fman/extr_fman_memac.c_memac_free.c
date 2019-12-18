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
struct fman_mac {struct fman_mac* memac_drv_param; TYPE_2__* pcsphy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ mdio; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_init_resources (struct fman_mac*) ; 
 int /*<<< orphan*/  kfree (struct fman_mac*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

int memac_free(struct fman_mac *memac)
{
	free_init_resources(memac);

	if (memac->pcsphy)
		put_device(&memac->pcsphy->mdio.dev);

	kfree(memac->memac_drv_param);
	kfree(memac);

	return 0;
}