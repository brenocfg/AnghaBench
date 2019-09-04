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
struct spi_nor {struct aspeed_smc_chip* priv; } ;
struct aspeed_smc_chip {TYPE_1__* controller; } ;
typedef  enum spi_nor_ops { ____Placeholder_spi_nor_ops } spi_nor_ops ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aspeed_smc_unprep(struct spi_nor *nor, enum spi_nor_ops ops)
{
	struct aspeed_smc_chip *chip = nor->priv;

	mutex_unlock(&chip->controller->mutex);
}