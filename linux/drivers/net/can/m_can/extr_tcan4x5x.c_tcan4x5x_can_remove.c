#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tcan4x5x_priv {int /*<<< orphan*/  mcan_dev; int /*<<< orphan*/  power; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_can_class_unregister (int /*<<< orphan*/ ) ; 
 struct tcan4x5x_priv* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  tcan4x5x_power_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcan4x5x_can_remove(struct spi_device *spi)
{
	struct tcan4x5x_priv *priv = spi_get_drvdata(spi);

	tcan4x5x_power_enable(priv->power, 0);

	m_can_class_unregister(priv->mcan_dev);

	return 0;
}