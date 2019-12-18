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
typedef  int u32 ;
struct TYPE_5__ {unsigned char bus_width; int flags; } ;
struct TYPE_6__ {TYPE_2__ parallel; } ;
struct v4l2_fwnode_endpoint {int bus_type; TYPE_3__ bus; } ;
struct TYPE_4__ {scalar_t__ field; } ;
struct sun6i_csi {TYPE_1__ config; struct v4l2_fwnode_endpoint v4l2_ep; } ;
struct sun6i_csi_dev {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; struct sun6i_csi csi; } ;

/* Variables and functions */
 int CSI_IF_CFG_CLK_POL_FALLING_EDGE ; 
 int CSI_IF_CFG_CLK_POL_MASK ; 
 int CSI_IF_CFG_CSI_IF_BT1120 ; 
 int CSI_IF_CFG_CSI_IF_BT656 ; 
 int CSI_IF_CFG_CSI_IF_MASK ; 
 int CSI_IF_CFG_CSI_IF_YUV422_16BIT ; 
 int CSI_IF_CFG_CSI_IF_YUV422_INTLV ; 
 int CSI_IF_CFG_FIELD_MASK ; 
 int CSI_IF_CFG_FIELD_POSITIVE ; 
 int CSI_IF_CFG_HREF_POL_MASK ; 
 int CSI_IF_CFG_HREF_POL_POSITIVE ; 
 int CSI_IF_CFG_IF_DATA_WIDTH_10BIT ; 
 int CSI_IF_CFG_IF_DATA_WIDTH_12BIT ; 
 int CSI_IF_CFG_IF_DATA_WIDTH_8BIT ; 
 int CSI_IF_CFG_IF_DATA_WIDTH_MASK ; 
 int CSI_IF_CFG_MIPI_IF_CSI ; 
 int CSI_IF_CFG_MIPI_IF_MASK ; 
 int /*<<< orphan*/  CSI_IF_CFG_REG ; 
 int CSI_IF_CFG_SRC_TYPE_INTERLACED ; 
 int CSI_IF_CFG_SRC_TYPE_MASK ; 
 int CSI_IF_CFG_SRC_TYPE_PROGRESSED ; 
 int CSI_IF_CFG_VREF_POL_MASK ; 
 int CSI_IF_CFG_VREF_POL_POSITIVE ; 
 scalar_t__ V4L2_FIELD_INTERLACED ; 
 scalar_t__ V4L2_FIELD_INTERLACED_BT ; 
 scalar_t__ V4L2_FIELD_INTERLACED_TB ; 
#define  V4L2_MBUS_BT656 129 
 int V4L2_MBUS_FIELD_EVEN_LOW ; 
 int V4L2_MBUS_HSYNC_ACTIVE_LOW ; 
#define  V4L2_MBUS_PARALLEL 128 
 int V4L2_MBUS_PCLK_SAMPLE_FALLING ; 
 int V4L2_MBUS_PCLK_SAMPLE_RISING ; 
 int V4L2_MBUS_VSYNC_ACTIVE_LOW ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned char) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sun6i_csi_setup_bus(struct sun6i_csi_dev *sdev)
{
	struct v4l2_fwnode_endpoint *endpoint = &sdev->csi.v4l2_ep;
	struct sun6i_csi *csi = &sdev->csi;
	unsigned char bus_width;
	u32 flags;
	u32 cfg;
	bool input_interlaced = false;

	if (csi->config.field == V4L2_FIELD_INTERLACED
	    || csi->config.field == V4L2_FIELD_INTERLACED_TB
	    || csi->config.field == V4L2_FIELD_INTERLACED_BT)
		input_interlaced = true;

	bus_width = endpoint->bus.parallel.bus_width;

	regmap_read(sdev->regmap, CSI_IF_CFG_REG, &cfg);

	cfg &= ~(CSI_IF_CFG_CSI_IF_MASK | CSI_IF_CFG_MIPI_IF_MASK |
		 CSI_IF_CFG_IF_DATA_WIDTH_MASK |
		 CSI_IF_CFG_CLK_POL_MASK | CSI_IF_CFG_VREF_POL_MASK |
		 CSI_IF_CFG_HREF_POL_MASK | CSI_IF_CFG_FIELD_MASK |
		 CSI_IF_CFG_SRC_TYPE_MASK);

	if (input_interlaced)
		cfg |= CSI_IF_CFG_SRC_TYPE_INTERLACED;
	else
		cfg |= CSI_IF_CFG_SRC_TYPE_PROGRESSED;

	switch (endpoint->bus_type) {
	case V4L2_MBUS_PARALLEL:
		cfg |= CSI_IF_CFG_MIPI_IF_CSI;

		flags = endpoint->bus.parallel.flags;

		cfg |= (bus_width == 16) ? CSI_IF_CFG_CSI_IF_YUV422_16BIT :
					   CSI_IF_CFG_CSI_IF_YUV422_INTLV;

		if (flags & V4L2_MBUS_FIELD_EVEN_LOW)
			cfg |= CSI_IF_CFG_FIELD_POSITIVE;

		if (flags & V4L2_MBUS_VSYNC_ACTIVE_LOW)
			cfg |= CSI_IF_CFG_VREF_POL_POSITIVE;
		if (flags & V4L2_MBUS_HSYNC_ACTIVE_LOW)
			cfg |= CSI_IF_CFG_HREF_POL_POSITIVE;

		if (flags & V4L2_MBUS_PCLK_SAMPLE_RISING)
			cfg |= CSI_IF_CFG_CLK_POL_FALLING_EDGE;
		break;
	case V4L2_MBUS_BT656:
		cfg |= CSI_IF_CFG_MIPI_IF_CSI;

		flags = endpoint->bus.parallel.flags;

		cfg |= (bus_width == 16) ? CSI_IF_CFG_CSI_IF_BT1120 :
					   CSI_IF_CFG_CSI_IF_BT656;

		if (flags & V4L2_MBUS_FIELD_EVEN_LOW)
			cfg |= CSI_IF_CFG_FIELD_POSITIVE;

		if (flags & V4L2_MBUS_PCLK_SAMPLE_FALLING)
			cfg |= CSI_IF_CFG_CLK_POL_FALLING_EDGE;
		break;
	default:
		dev_warn(sdev->dev, "Unsupported bus type: %d\n",
			 endpoint->bus_type);
		break;
	}

	switch (bus_width) {
	case 8:
		cfg |= CSI_IF_CFG_IF_DATA_WIDTH_8BIT;
		break;
	case 10:
		cfg |= CSI_IF_CFG_IF_DATA_WIDTH_10BIT;
		break;
	case 12:
		cfg |= CSI_IF_CFG_IF_DATA_WIDTH_12BIT;
		break;
	case 16: /* No need to configure DATA_WIDTH for 16bit */
		break;
	default:
		dev_warn(sdev->dev, "Unsupported bus width: %u\n", bus_width);
		break;
	}

	regmap_write(sdev->regmap, CSI_IF_CFG_REG, cfg);
}