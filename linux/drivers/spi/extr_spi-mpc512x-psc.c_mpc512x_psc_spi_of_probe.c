#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  irq_of_parse_and_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mpc512x_psc_spi_do_probe (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * of_get_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ of_translate_address (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int mpc512x_psc_spi_of_probe(struct platform_device *op)
{
	const u32 *regaddr_p;
	u64 regaddr64, size64;

	regaddr_p = of_get_address(op->dev.of_node, 0, &size64, NULL);
	if (!regaddr_p) {
		dev_err(&op->dev, "Invalid PSC address\n");
		return -EINVAL;
	}
	regaddr64 = of_translate_address(op->dev.of_node, regaddr_p);

	return mpc512x_psc_spi_do_probe(&op->dev, (u32) regaddr64, (u32) size64,
				irq_of_parse_and_map(op->dev.of_node, 0));
}