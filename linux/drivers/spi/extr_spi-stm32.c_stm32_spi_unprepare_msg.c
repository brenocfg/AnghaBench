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
struct stm32_spi {TYPE_1__* cfg; } ;
struct spi_message {int dummy; } ;
struct spi_master {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable ) (struct stm32_spi*) ;} ;

/* Variables and functions */
 struct stm32_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  stub1 (struct stm32_spi*) ; 

__attribute__((used)) static int stm32_spi_unprepare_msg(struct spi_master *master,
				   struct spi_message *msg)
{
	struct stm32_spi *spi = spi_master_get_devdata(master);

	spi->cfg->disable(spi);

	return 0;
}