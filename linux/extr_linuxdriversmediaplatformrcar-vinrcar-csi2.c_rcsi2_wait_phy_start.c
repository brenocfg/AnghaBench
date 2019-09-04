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
typedef  int u32 ;
struct rcar_csi2 {int lanes; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  PHCLM_REG ; 
 int const PHCLM_STOPSTATECKL ; 
 int /*<<< orphan*/  PHDLM_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int const rcsi2_read (struct rcar_csi2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int rcsi2_wait_phy_start(struct rcar_csi2 *priv)
{
	unsigned int timeout;

	/* Wait for the clock and data lanes to enter LP-11 state. */
	for (timeout = 0; timeout <= 20; timeout++) {
		const u32 lane_mask = (1 << priv->lanes) - 1;

		if ((rcsi2_read(priv, PHCLM_REG) & PHCLM_STOPSTATECKL)  &&
		    (rcsi2_read(priv, PHDLM_REG) & lane_mask) == lane_mask)
			return 0;

		usleep_range(1000, 2000);
	}

	dev_err(priv->dev, "Timeout waiting for LP-11 state\n");

	return -ETIMEDOUT;
}