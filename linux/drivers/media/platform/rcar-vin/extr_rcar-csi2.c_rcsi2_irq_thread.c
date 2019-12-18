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
struct rcar_csi2 {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rcsi2_start (struct rcar_csi2*) ; 
 int /*<<< orphan*/  rcsi2_stop (struct rcar_csi2*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static irqreturn_t rcsi2_irq_thread(int irq, void *data)
{
	struct rcar_csi2 *priv = data;

	mutex_lock(&priv->lock);
	rcsi2_stop(priv);
	usleep_range(1000, 2000);
	if (rcsi2_start(priv))
		dev_warn(priv->dev, "Failed to restart CSI-2 receiver\n");
	mutex_unlock(&priv->lock);

	return IRQ_HANDLED;
}