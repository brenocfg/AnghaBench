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
struct ov965x {void** gpios; TYPE_1__* client; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 size_t GPIO_PWDN ; 
 size_t GPIO_RST ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char*) ; 
 void* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov965x_configure_gpios(struct ov965x *ov965x)
{
	struct device *dev = &ov965x->client->dev;

	ov965x->gpios[GPIO_PWDN] = devm_gpiod_get_optional(dev, "powerdown",
							GPIOD_OUT_HIGH);
	if (IS_ERR(ov965x->gpios[GPIO_PWDN])) {
		dev_info(dev, "can't get %s GPIO\n", "powerdown");
		return PTR_ERR(ov965x->gpios[GPIO_PWDN]);
	}

	ov965x->gpios[GPIO_RST] = devm_gpiod_get_optional(dev, "reset",
							GPIOD_OUT_HIGH);
	if (IS_ERR(ov965x->gpios[GPIO_RST])) {
		dev_info(dev, "can't get %s GPIO\n", "reset");
		return PTR_ERR(ov965x->gpios[GPIO_RST]);
	}

	return 0;
}