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
struct reg_field {int dummy; } ;
struct opp_table {int dummy; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct TYPE_2__ {struct device* cpu; } ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 int DEFAULT_VERSION ; 
 int ENODEV ; 
 int /*<<< orphan*/  HW_INFO_INDEX ; 
 scalar_t__ IS_ERR (struct opp_table*) ; 
 int MAX_PCODE_NAME_LEN ; 
 int /*<<< orphan*/  PCODE ; 
 int PTR_ERR (struct opp_table*) ; 
 int /*<<< orphan*/  SUBSTRATE ; 
 int VERSION_ELEMENTS ; 
 TYPE_1__ ddata ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int,unsigned int,unsigned int,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct opp_table* dev_pm_opp_set_prop_name (struct device*,char*) ; 
 struct opp_table* dev_pm_opp_set_supported_hw (struct device*,unsigned int*,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int of_property_read_u32_index (struct device_node*,char*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int sti_cpufreq_fetch_major () ; 
 int sti_cpufreq_fetch_minor () ; 
 int sti_cpufreq_fetch_regmap_field (struct reg_field const*,unsigned int,int /*<<< orphan*/ ) ; 
 struct reg_field* sti_cpufreq_match () ; 

__attribute__((used)) static int sti_cpufreq_set_opp_info(void)
{
	struct device *dev = ddata.cpu;
	struct device_node *np = dev->of_node;
	const struct reg_field *reg_fields;
	unsigned int hw_info_offset;
	unsigned int version[VERSION_ELEMENTS];
	int pcode, substrate, major, minor;
	int ret;
	char name[MAX_PCODE_NAME_LEN];
	struct opp_table *opp_table;

	reg_fields = sti_cpufreq_match();
	if (!reg_fields) {
		dev_err(dev, "This SoC doesn't support voltage scaling\n");
		return -ENODEV;
	}

	ret = of_property_read_u32_index(np, "st,syscfg-eng",
					 HW_INFO_INDEX, &hw_info_offset);
	if (ret) {
		dev_warn(dev, "Failed to read HW info offset from DT\n");
		substrate = DEFAULT_VERSION;
		pcode = 0;
		goto use_defaults;
	}

	pcode = sti_cpufreq_fetch_regmap_field(reg_fields,
					       hw_info_offset,
					       PCODE);
	if (pcode < 0) {
		dev_warn(dev, "Failed to obtain process code\n");
		/* Use default pcode */
		pcode = 0;
	}

	substrate = sti_cpufreq_fetch_regmap_field(reg_fields,
						   hw_info_offset,
						   SUBSTRATE);
	if (substrate) {
		dev_warn(dev, "Failed to obtain substrate code\n");
		/* Use default substrate */
		substrate = DEFAULT_VERSION;
	}

use_defaults:
	major = sti_cpufreq_fetch_major();
	if (major < 0) {
		dev_err(dev, "Failed to obtain major version\n");
		/* Use default major number */
		major = DEFAULT_VERSION;
	}

	minor = sti_cpufreq_fetch_minor();
	if (minor < 0) {
		dev_err(dev, "Failed to obtain minor version\n");
		/* Use default minor number */
		minor = DEFAULT_VERSION;
	}

	snprintf(name, MAX_PCODE_NAME_LEN, "pcode%d", pcode);

	opp_table = dev_pm_opp_set_prop_name(dev, name);
	if (IS_ERR(opp_table)) {
		dev_err(dev, "Failed to set prop name\n");
		return PTR_ERR(opp_table);
	}

	version[0] = BIT(major);
	version[1] = BIT(minor);
	version[2] = BIT(substrate);

	opp_table = dev_pm_opp_set_supported_hw(dev, version, VERSION_ELEMENTS);
	if (IS_ERR(opp_table)) {
		dev_err(dev, "Failed to set supported hardware\n");
		return PTR_ERR(opp_table);
	}

	dev_dbg(dev, "pcode: %d major: %d minor: %d substrate: %d\n",
		pcode, major, minor, substrate);
	dev_dbg(dev, "version[0]: %x version[1]: %x version[2]: %x\n",
		version[0], version[1], version[2]);

	return 0;
}