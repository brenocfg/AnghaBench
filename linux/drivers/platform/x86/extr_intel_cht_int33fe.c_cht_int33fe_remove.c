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
struct cht_int33fe_data {int /*<<< orphan*/  max17047; int /*<<< orphan*/  fusb302; int /*<<< orphan*/  pi3usb30532; } ;

/* Variables and functions */
 int /*<<< orphan*/  cht_int33fe_remove_nodes (struct cht_int33fe_data*) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 struct cht_int33fe_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int cht_int33fe_remove(struct platform_device *pdev)
{
	struct cht_int33fe_data *data = platform_get_drvdata(pdev);

	i2c_unregister_device(data->pi3usb30532);
	i2c_unregister_device(data->fusb302);
	i2c_unregister_device(data->max17047);

	cht_int33fe_remove_nodes(data);

	return 0;
}