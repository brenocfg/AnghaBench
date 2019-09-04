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
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  name2 ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,char const*,int) ; 
 int of_get_named_gpio (struct device_node*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 scalar_t__ sscanf (char*,char*,char*) ; 

__attribute__((used)) static int msm_hdmi_get_gpio(struct device_node *of_node, const char *name)
{
	int gpio;

	/* try with the gpio names as in the table (downstream bindings) */
	gpio = of_get_named_gpio(of_node, name, 0);
	if (gpio < 0) {
		char name2[32];

		/* try with the gpio names as in the upstream bindings */
		snprintf(name2, sizeof(name2), "%s-gpios", name);
		gpio = of_get_named_gpio(of_node, name2, 0);
		if (gpio < 0) {
			char name3[32];

			/*
			 * try again after stripping out the "qcom,hdmi-tx"
			 * prefix. This is mainly to match "hpd-gpios" used
			 * in the upstream bindings
			 */
			if (sscanf(name2, "qcom,hdmi-tx-%s", name3))
				gpio = of_get_named_gpio(of_node, name3, 0);
		}

		if (gpio < 0) {
			DBG("failed to get gpio: %s (%d)", name, gpio);
			gpio = -1;
		}
	}
	return gpio;
}