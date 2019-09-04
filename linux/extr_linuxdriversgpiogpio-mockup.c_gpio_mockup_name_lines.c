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
struct gpio_chip {int ngpio; char const* const* names; int /*<<< orphan*/  label; } ;
struct gpio_mockup_chip {struct gpio_chip gc; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* devm_kasprintf (struct device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 char** devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gpio_mockup_name_lines(struct device *dev,
				  struct gpio_mockup_chip *chip)
{
	struct gpio_chip *gc = &chip->gc;
	char **names;
	int i;

	names = devm_kcalloc(dev, gc->ngpio, sizeof(char *), GFP_KERNEL);
	if (!names)
		return -ENOMEM;

	for (i = 0; i < gc->ngpio; i++) {
		names[i] = devm_kasprintf(dev, GFP_KERNEL,
					  "%s-%d", gc->label, i);
		if (!names[i])
			return -ENOMEM;
	}

	gc->names = (const char *const *)names;

	return 0;
}