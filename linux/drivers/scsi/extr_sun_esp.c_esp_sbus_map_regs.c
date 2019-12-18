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
struct resource {int dummy; } ;
struct platform_device {struct resource* resource; } ;
struct esp {int /*<<< orphan*/  regs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SBUS_ESP_REG_SIZE ; 
 int /*<<< orphan*/  of_ioremap (struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int esp_sbus_map_regs(struct esp *esp, int hme)
{
	struct platform_device *op = to_platform_device(esp->dev);
	struct resource *res;

	/* On HME, two reg sets exist, first is DVMA,
	 * second is ESP registers.
	 */
	if (hme)
		res = &op->resource[1];
	else
		res = &op->resource[0];

	esp->regs = of_ioremap(res, 0, SBUS_ESP_REG_SIZE, "ESP");
	if (!esp->regs)
		return -ENOMEM;

	return 0;
}