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
struct mrfld_pinctrl {unsigned int nfamilies; int /*<<< orphan*/  dev; struct mrfld_family* families; } ;
struct mrfld_family {unsigned int pin_base; unsigned int npins; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static const struct mrfld_family *mrfld_get_family(struct mrfld_pinctrl *mp,
						   unsigned int pin)
{
	const struct mrfld_family *family;
	unsigned int i;

	for (i = 0; i < mp->nfamilies; i++) {
		family = &mp->families[i];
		if (pin >= family->pin_base &&
		    pin < family->pin_base + family->npins)
			return family;
	}

	dev_warn(mp->dev, "failed to find family for pin %u\n", pin);
	return NULL;
}