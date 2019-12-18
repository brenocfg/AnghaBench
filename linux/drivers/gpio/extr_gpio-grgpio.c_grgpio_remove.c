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
struct platform_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  bgpio_lock; } ;
struct grgpio_priv {TYPE_2__ gc; scalar_t__ domain; TYPE_1__* uirqs; } ;
struct TYPE_3__ {scalar_t__ refcnt; } ;

/* Variables and functions */
 int EBUSY ; 
 int GRGPIO_MAX_NGPIO ; 
 int /*<<< orphan*/  gpiochip_remove (TYPE_2__*) ; 
 int /*<<< orphan*/  irq_domain_remove (scalar_t__) ; 
 struct grgpio_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int grgpio_remove(struct platform_device *ofdev)
{
	struct grgpio_priv *priv = platform_get_drvdata(ofdev);
	unsigned long flags;
	int i;
	int ret = 0;

	spin_lock_irqsave(&priv->gc.bgpio_lock, flags);

	if (priv->domain) {
		for (i = 0; i < GRGPIO_MAX_NGPIO; i++) {
			if (priv->uirqs[i].refcnt != 0) {
				ret = -EBUSY;
				goto out;
			}
		}
	}

	gpiochip_remove(&priv->gc);

	if (priv->domain)
		irq_domain_remove(priv->domain);

out:
	spin_unlock_irqrestore(&priv->gc.bgpio_lock, flags);

	return ret;
}