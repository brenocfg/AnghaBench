#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int num_data_lanes; unsigned int* data_lanes; } ;
struct TYPE_6__ {TYPE_2__ mipi_csi2; } ;
struct TYPE_4__ {scalar_t__ id; scalar_t__ port; } ;
struct v4l2_fwnode_endpoint {scalar_t__ bus_type; TYPE_3__ bus; TYPE_1__ base; } ;
struct rcar_csi2 {int lanes; unsigned int* lane_swap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 int EINVAL ; 
 int ENOTCONN ; 
 scalar_t__ V4L2_MBUS_CSI2_DPHY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int rcsi2_parse_v4l2(struct rcar_csi2 *priv,
			    struct v4l2_fwnode_endpoint *vep)
{
	unsigned int i;

	/* Only port 0 endpoint 0 is valid. */
	if (vep->base.port || vep->base.id)
		return -ENOTCONN;

	if (vep->bus_type != V4L2_MBUS_CSI2_DPHY) {
		dev_err(priv->dev, "Unsupported bus: %u\n", vep->bus_type);
		return -EINVAL;
	}

	priv->lanes = vep->bus.mipi_csi2.num_data_lanes;
	if (priv->lanes != 1 && priv->lanes != 2 && priv->lanes != 4) {
		dev_err(priv->dev, "Unsupported number of data-lanes: %u\n",
			priv->lanes);
		return -EINVAL;
	}

	for (i = 0; i < ARRAY_SIZE(priv->lane_swap); i++) {
		priv->lane_swap[i] = i < priv->lanes ?
			vep->bus.mipi_csi2.data_lanes[i] : i;

		/* Check for valid lane number. */
		if (priv->lane_swap[i] < 1 || priv->lane_swap[i] > 4) {
			dev_err(priv->dev, "data-lanes must be in 1-4 range\n");
			return -EINVAL;
		}
	}

	return 0;
}