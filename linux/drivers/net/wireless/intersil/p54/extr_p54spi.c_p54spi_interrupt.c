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
struct p54s_priv {int /*<<< orphan*/  work; int /*<<< orphan*/  hw; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct p54s_priv* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static irqreturn_t p54spi_interrupt(int irq, void *config)
{
	struct spi_device *spi = config;
	struct p54s_priv *priv = spi_get_drvdata(spi);

	ieee80211_queue_work(priv->hw, &priv->work);

	return IRQ_HANDLED;
}