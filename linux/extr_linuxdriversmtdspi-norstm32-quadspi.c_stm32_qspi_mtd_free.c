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
struct stm32_qspi {TYPE_2__* flash; } ;
struct TYPE_3__ {int /*<<< orphan*/  mtd; } ;
struct TYPE_4__ {TYPE_1__ nor; scalar_t__ registered; } ;

/* Variables and functions */
 int STM32_MAX_NORCHIP ; 
 int /*<<< orphan*/  mtd_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stm32_qspi_mtd_free(struct stm32_qspi *qspi)
{
	int i;

	for (i = 0; i < STM32_MAX_NORCHIP; i++)
		if (qspi->flash[i].registered)
			mtd_device_unregister(&qspi->flash[i].nor.mtd);
}