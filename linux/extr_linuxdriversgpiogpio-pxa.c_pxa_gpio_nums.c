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
struct pxa_gpio_id {int type; int /*<<< orphan*/  gpio_nums; } ;
struct platform_device_id {scalar_t__ driver_data; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MMP2_GPIO 135 
#define  MMP_GPIO 134 
#define  PXA1928_GPIO 133 
#define  PXA25X_GPIO 132 
#define  PXA26X_GPIO 131 
#define  PXA27X_GPIO 130 
#define  PXA3XX_GPIO 129 
#define  PXA93X_GPIO 128 
 int gpio_type ; 
 struct platform_device_id* platform_get_device_id (struct platform_device*) ; 

__attribute__((used)) static int pxa_gpio_nums(struct platform_device *pdev)
{
	const struct platform_device_id *id = platform_get_device_id(pdev);
	struct pxa_gpio_id *pxa_id = (struct pxa_gpio_id *)id->driver_data;
	int count = 0;

	switch (pxa_id->type) {
	case PXA25X_GPIO:
	case PXA26X_GPIO:
	case PXA27X_GPIO:
	case PXA3XX_GPIO:
	case PXA93X_GPIO:
	case MMP_GPIO:
	case MMP2_GPIO:
	case PXA1928_GPIO:
		gpio_type = pxa_id->type;
		count = pxa_id->gpio_nums - 1;
		break;
	default:
		count = -EINVAL;
		break;
	}
	return count;
}