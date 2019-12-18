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
typedef  int /*<<< orphan*/  u16 ;
struct rcsi2_mbps_reg {int mbps; int /*<<< orphan*/  reg; } ;
struct rcar_csi2 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int rcsi2_phtw_write (struct rcar_csi2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rcsi2_phtw_write_mbps(struct rcar_csi2 *priv, unsigned int mbps,
				 const struct rcsi2_mbps_reg *values, u16 code)
{
	const struct rcsi2_mbps_reg *value;

	for (value = values; value->mbps; value++)
		if (value->mbps >= mbps)
			break;

	if (!value->mbps) {
		dev_err(priv->dev, "Unsupported PHY speed (%u Mbps)", mbps);
		return -ERANGE;
	}

	return rcsi2_phtw_write(priv, value->reg, code);
}