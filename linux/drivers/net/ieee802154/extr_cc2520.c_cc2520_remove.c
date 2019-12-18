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
struct cc2520_private {int /*<<< orphan*/  hw; int /*<<< orphan*/  fifop_irqwork; int /*<<< orphan*/  buffer_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee802154_free_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee802154_unregister_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct cc2520_private* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int cc2520_remove(struct spi_device *spi)
{
	struct cc2520_private *priv = spi_get_drvdata(spi);

	mutex_destroy(&priv->buffer_mutex);
	flush_work(&priv->fifop_irqwork);

	ieee802154_unregister_hw(priv->hw);
	ieee802154_free_hw(priv->hw);

	return 0;
}