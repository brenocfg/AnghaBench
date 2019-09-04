#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct tegra_gmi {int /*<<< orphan*/  snor_timing1; int /*<<< orphan*/  snor_timing0; int /*<<< orphan*/  snor_config; TYPE_1__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  TEGRA_GMI_ADV_ACTIVE_HIGH ; 
 int /*<<< orphan*/  TEGRA_GMI_ADV_WIDTH (int) ; 
 int /*<<< orphan*/  TEGRA_GMI_BUS_WIDTH_32BIT ; 
 int /*<<< orphan*/  TEGRA_GMI_CE_WIDTH (int) ; 
 int /*<<< orphan*/  TEGRA_GMI_CS_ACTIVE_HIGH ; 
 int /*<<< orphan*/  TEGRA_GMI_CS_SELECT (scalar_t__) ; 
 int /*<<< orphan*/  TEGRA_GMI_HOLD_WIDTH (int) ; 
 scalar_t__ TEGRA_GMI_MAX_CHIP_SELECT ; 
 int /*<<< orphan*/  TEGRA_GMI_MUXED_WIDTH (int) ; 
 int /*<<< orphan*/  TEGRA_GMI_MUX_MODE ; 
 int /*<<< orphan*/  TEGRA_GMI_OE_ACTIVE_HIGH ; 
 int /*<<< orphan*/  TEGRA_GMI_OE_WIDTH (int) ; 
 int /*<<< orphan*/  TEGRA_GMI_RDY_ACTIVE_HIGH ; 
 int /*<<< orphan*/  TEGRA_GMI_RDY_BEFORE_DATA ; 
 int /*<<< orphan*/  TEGRA_GMI_WAIT_WIDTH (int) ; 
 int /*<<< orphan*/  TEGRA_GMI_WE_WIDTH (int) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 int of_get_child_count (int /*<<< orphan*/ ) ; 
 struct device_node* of_get_next_available_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 int of_property_read_u32_array (struct device_node*,char*,scalar_t__*,int) ; 

__attribute__((used)) static int tegra_gmi_parse_dt(struct tegra_gmi *gmi)
{
	struct device_node *child;
	u32 property, ranges[4];
	int err;

	child = of_get_next_available_child(gmi->dev->of_node, NULL);
	if (!child) {
		dev_err(gmi->dev, "no child nodes found\n");
		return -ENODEV;
	}

	/*
	 * We currently only support one child device due to lack of
	 * chip-select address decoding. Which means that we only have one
	 * chip-select line from the GMI controller.
	 */
	if (of_get_child_count(gmi->dev->of_node) > 1)
		dev_warn(gmi->dev, "only one child device is supported.");

	if (of_property_read_bool(child, "nvidia,snor-data-width-32bit"))
		gmi->snor_config |= TEGRA_GMI_BUS_WIDTH_32BIT;

	if (of_property_read_bool(child, "nvidia,snor-mux-mode"))
		gmi->snor_config |= TEGRA_GMI_MUX_MODE;

	if (of_property_read_bool(child, "nvidia,snor-rdy-active-before-data"))
		gmi->snor_config |= TEGRA_GMI_RDY_BEFORE_DATA;

	if (of_property_read_bool(child, "nvidia,snor-rdy-active-high"))
		gmi->snor_config |= TEGRA_GMI_RDY_ACTIVE_HIGH;

	if (of_property_read_bool(child, "nvidia,snor-adv-active-high"))
		gmi->snor_config |= TEGRA_GMI_ADV_ACTIVE_HIGH;

	if (of_property_read_bool(child, "nvidia,snor-oe-active-high"))
		gmi->snor_config |= TEGRA_GMI_OE_ACTIVE_HIGH;

	if (of_property_read_bool(child, "nvidia,snor-cs-active-high"))
		gmi->snor_config |= TEGRA_GMI_CS_ACTIVE_HIGH;

	/* Decode the CS# */
	err = of_property_read_u32_array(child, "ranges", ranges, 4);
	if (err < 0) {
		/* Invalid binding */
		if (err == -EOVERFLOW) {
			dev_err(gmi->dev,
				"failed to decode CS: invalid ranges length\n");
			goto error_cs;
		}

		/*
		 * If we reach here it means that the child node has an empty
		 * ranges or it does not exist at all. Attempt to decode the
		 * CS# from the reg property instead.
		 */
		err = of_property_read_u32(child, "reg", &property);
		if (err < 0) {
			dev_err(gmi->dev,
				"failed to decode CS: no reg property found\n");
			goto error_cs;
		}
	} else {
		property = ranges[1];
	}

	/* Valid chip selects are CS0-CS7 */
	if (property >= TEGRA_GMI_MAX_CHIP_SELECT) {
		dev_err(gmi->dev, "invalid chip select: %d", property);
		err = -EINVAL;
		goto error_cs;
	}

	gmi->snor_config |= TEGRA_GMI_CS_SELECT(property);

	/* The default values that are provided below are reset values */
	if (!of_property_read_u32(child, "nvidia,snor-muxed-width", &property))
		gmi->snor_timing0 |= TEGRA_GMI_MUXED_WIDTH(property);
	else
		gmi->snor_timing0 |= TEGRA_GMI_MUXED_WIDTH(1);

	if (!of_property_read_u32(child, "nvidia,snor-hold-width", &property))
		gmi->snor_timing0 |= TEGRA_GMI_HOLD_WIDTH(property);
	else
		gmi->snor_timing0 |= TEGRA_GMI_HOLD_WIDTH(1);

	if (!of_property_read_u32(child, "nvidia,snor-adv-width", &property))
		gmi->snor_timing0 |= TEGRA_GMI_ADV_WIDTH(property);
	else
		gmi->snor_timing0 |= TEGRA_GMI_ADV_WIDTH(1);

	if (!of_property_read_u32(child, "nvidia,snor-ce-width", &property))
		gmi->snor_timing0 |= TEGRA_GMI_CE_WIDTH(property);
	else
		gmi->snor_timing0 |= TEGRA_GMI_CE_WIDTH(4);

	if (!of_property_read_u32(child, "nvidia,snor-we-width", &property))
		gmi->snor_timing1 |= TEGRA_GMI_WE_WIDTH(property);
	else
		gmi->snor_timing1 |= TEGRA_GMI_WE_WIDTH(1);

	if (!of_property_read_u32(child, "nvidia,snor-oe-width", &property))
		gmi->snor_timing1 |= TEGRA_GMI_OE_WIDTH(property);
	else
		gmi->snor_timing1 |= TEGRA_GMI_OE_WIDTH(1);

	if (!of_property_read_u32(child, "nvidia,snor-wait-width", &property))
		gmi->snor_timing1 |= TEGRA_GMI_WAIT_WIDTH(property);
	else
		gmi->snor_timing1 |= TEGRA_GMI_WAIT_WIDTH(3);

error_cs:
	of_node_put(child);
	return err;
}