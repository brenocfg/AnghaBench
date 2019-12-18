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
struct intel_pinctrl {int ncommunities; int /*<<< orphan*/  dev; struct intel_community* communities; } ;
struct intel_community {unsigned int pin_base; unsigned int npins; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static struct intel_community *intel_get_community(struct intel_pinctrl *pctrl,
						   unsigned int pin)
{
	struct intel_community *community;
	int i;

	for (i = 0; i < pctrl->ncommunities; i++) {
		community = &pctrl->communities[i];
		if (pin >= community->pin_base &&
		    pin < community->pin_base + community->npins)
			return community;
	}

	dev_warn(pctrl->dev, "failed to find community for pin %u\n", pin);
	return NULL;
}