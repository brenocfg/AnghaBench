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
struct spi_device {int dummy; } ;
struct sja1105_private {int /*<<< orphan*/  ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsa_unregister_switch (int /*<<< orphan*/ ) ; 
 struct sja1105_private* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int sja1105_remove(struct spi_device *spi)
{
	struct sja1105_private *priv = spi_get_drvdata(spi);

	dsa_unregister_switch(priv->ds);
	return 0;
}