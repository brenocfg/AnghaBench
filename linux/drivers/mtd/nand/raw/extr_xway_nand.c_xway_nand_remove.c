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
struct xway_nand_data {int /*<<< orphan*/  chip; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nand_release (int /*<<< orphan*/ *) ; 
 struct xway_nand_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int xway_nand_remove(struct platform_device *pdev)
{
	struct xway_nand_data *data = platform_get_drvdata(pdev);

	nand_release(&data->chip);

	return 0;
}