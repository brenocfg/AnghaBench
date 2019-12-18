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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct rza1_pinctrl {int /*<<< orphan*/  dev; struct pinctrl_dev* pctl; } ;
struct rza1_mux_conf {int id; scalar_t__ pin; int /*<<< orphan*/  port; scalar_t__ mux_flags; int /*<<< orphan*/  mux_func; } ;
struct property {int length; } ;
struct pinctrl_dev {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ MUX_FLAGS_SWIO_INPUT ; 
 scalar_t__ MUX_FLAGS_SWIO_OUTPUT ; 
 int /*<<< orphan*/  MUX_FUNC (int) ; 
 int MUX_PIN_ID_MASK ; 
#define  PIN_CONFIG_INPUT_ENABLE 129 
#define  PIN_CONFIG_OUTPUT 128 
 int /*<<< orphan*/  RZA1_NPORTS ; 
 scalar_t__ RZA1_PINS_PER_PORT ; 
 scalar_t__ RZA1_PIN_ID_TO_PIN (int) ; 
 int /*<<< orphan*/  RZA1_PIN_ID_TO_PORT (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  kfree (unsigned long*) ; 
 struct property* of_find_property (struct device_node*,char const*,int /*<<< orphan*/ *) ; 
 int of_property_read_u32_index (struct device_node*,char const*,unsigned int,int*) ; 
 int pinconf_generic_parse_dt_config (struct device_node*,struct pinctrl_dev*,unsigned long**,unsigned int*) ; 
 int pinconf_to_config_param (unsigned long) ; 

__attribute__((used)) static int rza1_parse_pinmux_node(struct rza1_pinctrl *rza1_pctl,
				  struct device_node *np,
				  struct rza1_mux_conf *mux_confs,
				  unsigned int *grpins)
{
	struct pinctrl_dev *pctldev = rza1_pctl->pctl;
	char const *prop_name = "pinmux";
	unsigned long *pin_configs;
	unsigned int npin_configs;
	struct property *of_pins;
	unsigned int npins;
	u8 pinmux_flags;
	unsigned int i;
	int ret;

	of_pins = of_find_property(np, prop_name, NULL);
	if (!of_pins) {
		dev_dbg(rza1_pctl->dev, "Missing %s property\n", prop_name);
		return -ENOENT;
	}
	npins = of_pins->length / sizeof(u32);

	/*
	 * Collect pin configuration properties: they apply to all pins in
	 * this sub-node
	 */
	ret = pinconf_generic_parse_dt_config(np, pctldev, &pin_configs,
					      &npin_configs);
	if (ret) {
		dev_err(rza1_pctl->dev,
			"Unable to parse pin configuration options for %pOFn\n",
			np);
		return ret;
	}

	/*
	 * Create a mask with pinmux flags from pin configuration;
	 * very few pins (TIOC[0-4][A|B|C|D] require SWIO direction
	 * specified in device tree.
	 */
	pinmux_flags = 0;
	for (i = 0; i < npin_configs && pinmux_flags == 0; i++)
		switch (pinconf_to_config_param(pin_configs[i])) {
		case PIN_CONFIG_INPUT_ENABLE:
			pinmux_flags |= MUX_FLAGS_SWIO_INPUT;
			break;
		case PIN_CONFIG_OUTPUT:
			pinmux_flags |= MUX_FLAGS_SWIO_OUTPUT;
		default:
			break;

		}

	kfree(pin_configs);

	/* Collect pin positions and their mux settings. */
	for (i = 0; i < npins; ++i) {
		u32 of_pinconf;
		struct rza1_mux_conf *mux_conf = &mux_confs[i];

		ret = of_property_read_u32_index(np, prop_name, i, &of_pinconf);
		if (ret)
			return ret;

		mux_conf->id		= of_pinconf & MUX_PIN_ID_MASK;
		mux_conf->port		= RZA1_PIN_ID_TO_PORT(mux_conf->id);
		mux_conf->pin		= RZA1_PIN_ID_TO_PIN(mux_conf->id);
		mux_conf->mux_func	= MUX_FUNC(of_pinconf);
		mux_conf->mux_flags	= pinmux_flags;

		if (mux_conf->port >= RZA1_NPORTS ||
		    mux_conf->pin >= RZA1_PINS_PER_PORT) {
			dev_err(rza1_pctl->dev,
				"Wrong port %u pin %u for %s property\n",
				mux_conf->port, mux_conf->pin, prop_name);
			return -EINVAL;
		}

		grpins[i] = mux_conf->id;
	}

	return npins;
}