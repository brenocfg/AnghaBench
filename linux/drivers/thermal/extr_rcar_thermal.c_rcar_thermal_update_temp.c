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
typedef  int u32 ;
struct rcar_thermal_priv {int ctemp; int /*<<< orphan*/  lock; int /*<<< orphan*/  id; TYPE_1__* chip; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ has_filonoff; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPCTL ; 
 int CTEMP ; 
 int EINVAL ; 
 int /*<<< orphan*/  FILONOFF ; 
 int /*<<< orphan*/  INTCTRL ; 
 int /*<<< orphan*/  POSNEG ; 
 int /*<<< orphan*/  THSCR ; 
 int /*<<< orphan*/  THSSR ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rcar_has_irq_support (struct rcar_thermal_priv*) ; 
 struct device* rcar_priv_to_dev (struct rcar_thermal_priv*) ; 
 int /*<<< orphan*/  rcar_thermal_bset (struct rcar_thermal_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rcar_thermal_read (struct rcar_thermal_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_thermal_write (struct rcar_thermal_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int rcar_thermal_update_temp(struct rcar_thermal_priv *priv)
{
	struct device *dev = rcar_priv_to_dev(priv);
	int i;
	u32 ctemp, old, new;
	int ret = -EINVAL;

	mutex_lock(&priv->lock);

	/*
	 * TSC decides a value of CPTAP automatically,
	 * and this is the conditions which validate interrupt.
	 */
	rcar_thermal_bset(priv, THSCR, CPCTL, CPCTL);

	ctemp = 0;
	old = ~0;
	for (i = 0; i < 128; i++) {
		/*
		 * we need to wait 300us after changing comparator offset
		 * to get stable temperature.
		 * see "Usage Notes" on datasheet
		 */
		udelay(300);

		new = rcar_thermal_read(priv, THSSR) & CTEMP;
		if (new == old) {
			ctemp = new;
			break;
		}
		old = new;
	}

	if (!ctemp) {
		dev_err(dev, "thermal sensor was broken\n");
		goto err_out_unlock;
	}

	/*
	 * enable IRQ
	 */
	if (rcar_has_irq_support(priv)) {
		if (priv->chip->has_filonoff)
			rcar_thermal_write(priv, FILONOFF, 0);

		/* enable Rising/Falling edge interrupt */
		rcar_thermal_write(priv, POSNEG,  0x1);
		rcar_thermal_write(priv, INTCTRL, (((ctemp - 0) << 8) |
						   ((ctemp - 1) << 0)));
	}

	dev_dbg(dev, "thermal%d  %d -> %d\n", priv->id, priv->ctemp, ctemp);

	priv->ctemp = ctemp;
	ret = 0;
err_out_unlock:
	mutex_unlock(&priv->lock);
	return ret;
}