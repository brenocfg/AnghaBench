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
struct hifmc_host {int num_chip; TYPE_1__** nor; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtd; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtd_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hisi_spi_nor_unregister_all(struct hifmc_host *host)
{
	int i;

	for (i = 0; i < host->num_chip; i++)
		mtd_device_unregister(&host->nor[i]->mtd);
}