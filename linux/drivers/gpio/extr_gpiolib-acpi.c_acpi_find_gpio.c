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
struct gpio_desc {int dummy; } ;
struct device {int dummy; } ;
struct acpi_gpio_info {scalar_t__ gpioint; } ;
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  propname ;
typedef  enum gpiod_flags { ____Placeholder_gpiod_flags } gpiod_flags ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (struct device*) ; 
 int ARRAY_SIZE (char**) ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct gpio_desc* ERR_CAST (struct gpio_desc*) ; 
 struct gpio_desc* ERR_PTR (int /*<<< orphan*/ ) ; 
 int GPIOD_OUT_HIGH ; 
 int GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  acpi_can_fallback_to_crs (struct acpi_device*,char const*) ; 
 struct gpio_desc* acpi_get_gpiod_by_index (struct acpi_device*,char*,unsigned int,struct acpi_gpio_info*) ; 
 int /*<<< orphan*/  acpi_gpio_update_gpiod_flags (int*,struct acpi_gpio_info*) ; 
 int /*<<< orphan*/  acpi_gpio_update_gpiod_lookup_flags (unsigned long*,struct acpi_gpio_info*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 char** gpio_suffixes ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 

struct gpio_desc *acpi_find_gpio(struct device *dev,
				 const char *con_id,
				 unsigned int idx,
				 enum gpiod_flags *dflags,
				 unsigned long *lookupflags)
{
	struct acpi_device *adev = ACPI_COMPANION(dev);
	struct acpi_gpio_info info;
	struct gpio_desc *desc;
	char propname[32];
	int i;

	/* Try first from _DSD */
	for (i = 0; i < ARRAY_SIZE(gpio_suffixes); i++) {
		if (con_id) {
			snprintf(propname, sizeof(propname), "%s-%s",
				 con_id, gpio_suffixes[i]);
		} else {
			snprintf(propname, sizeof(propname), "%s",
				 gpio_suffixes[i]);
		}

		desc = acpi_get_gpiod_by_index(adev, propname, idx, &info);
		if (!IS_ERR(desc))
			break;
		if (PTR_ERR(desc) == -EPROBE_DEFER)
			return ERR_CAST(desc);
	}

	/* Then from plain _CRS GPIOs */
	if (IS_ERR(desc)) {
		if (!acpi_can_fallback_to_crs(adev, con_id))
			return ERR_PTR(-ENOENT);

		desc = acpi_get_gpiod_by_index(adev, NULL, idx, &info);
		if (IS_ERR(desc))
			return desc;
	}

	if (info.gpioint &&
	    (*dflags == GPIOD_OUT_LOW || *dflags == GPIOD_OUT_HIGH)) {
		dev_dbg(dev, "refusing GpioInt() entry when doing GPIOD_OUT_* lookup\n");
		return ERR_PTR(-ENOENT);
	}

	acpi_gpio_update_gpiod_flags(dflags, &info);
	acpi_gpio_update_gpiod_lookup_flags(lookupflags, &info);
	return desc;
}