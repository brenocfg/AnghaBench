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
struct lpc18xx_dmamux_data {int /*<<< orphan*/  lock; } ;
struct lpc18xx_dmamux {int busy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct lpc18xx_dmamux_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void lpc18xx_dmamux_free(struct device *dev, void *route_data)
{
	struct lpc18xx_dmamux_data *dmamux = dev_get_drvdata(dev);
	struct lpc18xx_dmamux *mux = route_data;
	unsigned long flags;

	spin_lock_irqsave(&dmamux->lock, flags);
	mux->busy = false;
	spin_unlock_irqrestore(&dmamux->lock, flags);
}