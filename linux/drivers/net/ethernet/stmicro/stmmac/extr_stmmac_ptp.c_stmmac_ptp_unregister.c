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
struct stmmac_priv {TYPE_1__* dev; int /*<<< orphan*/ * ptp_clock; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptp_clock_unregister (int /*<<< orphan*/ *) ; 

void stmmac_ptp_unregister(struct stmmac_priv *priv)
{
	if (priv->ptp_clock) {
		ptp_clock_unregister(priv->ptp_clock);
		priv->ptp_clock = NULL;
		pr_debug("Removed PTP HW clock successfully on %s\n",
			 priv->dev->name);
	}
}