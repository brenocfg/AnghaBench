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
struct platform_device {int dummy; } ;
struct htcpld_data {struct htcpld_chip* chip; } ;
struct htcpld_chip {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 struct htcpld_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void htcpld_unregister_chip_i2c(
		struct platform_device *pdev,
		int chip_index)
{
	struct htcpld_data *htcpld;
	struct htcpld_chip *chip;

	/* Get the platform and driver data */
	htcpld = platform_get_drvdata(pdev);
	chip = &htcpld->chip[chip_index];

	i2c_unregister_device(chip->client);
}