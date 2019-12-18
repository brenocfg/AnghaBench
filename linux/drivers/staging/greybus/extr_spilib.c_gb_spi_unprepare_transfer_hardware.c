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
struct spi_master {int dummy; } ;
struct gb_spilib {int /*<<< orphan*/  parent; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unprepare_transfer_hardware ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct gb_spilib* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gb_spi_unprepare_transfer_hardware(struct spi_master *master)
{
	struct gb_spilib *spi = spi_master_get_devdata(master);

	spi->ops->unprepare_transfer_hardware(spi->parent);

	return 0;
}