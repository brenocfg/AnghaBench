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
struct rcsi2_mbps_reg {unsigned int mbps; int /*<<< orphan*/  reg; } ;
struct rcar_csi2 {int /*<<< orphan*/  dev; TYPE_1__* info; } ;
struct TYPE_2__ {struct rcsi2_mbps_reg* hsfreqrange; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  PHYPLL_HSFREQRANGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHYPLL_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  rcsi2_write (struct rcar_csi2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rcsi2_set_phypll(struct rcar_csi2 *priv, unsigned int mbps)
{
	const struct rcsi2_mbps_reg *hsfreq;

	for (hsfreq = priv->info->hsfreqrange; hsfreq->mbps != 0; hsfreq++)
		if (hsfreq->mbps >= mbps)
			break;

	if (!hsfreq->mbps) {
		dev_err(priv->dev, "Unsupported PHY speed (%u Mbps)", mbps);
		return -ERANGE;
	}

	rcsi2_write(priv, PHYPLL_REG, PHYPLL_HSFREQRANGE(hsfreq->reg));

	return 0;
}