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
struct omap_rng_dev {TYPE_1__* pdata; } ;
struct hwrng {scalar_t__ priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* cleanup ) (struct omap_rng_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct omap_rng_dev*) ; 

__attribute__((used)) static void omap_rng_cleanup(struct hwrng *rng)
{
	struct omap_rng_dev *priv;

	priv = (struct omap_rng_dev *)rng->priv;
	priv->pdata->cleanup(priv);
}