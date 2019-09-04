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
typedef  scalar_t__ u32 ;
struct lpc32xx_kscan_drv {int /*<<< orphan*/  scan_delay; int /*<<< orphan*/  deb_clks; int /*<<< orphan*/  row_shift; scalar_t__ matrix_sz; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  get_count_order (scalar_t__) ; 
 int matrix_keypad_parse_properties (struct device*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lpc32xx_parse_dt(struct device *dev,
				      struct lpc32xx_kscan_drv *kscandat)
{
	struct device_node *np = dev->of_node;
	u32 rows = 0, columns = 0;
	int err;

	err = matrix_keypad_parse_properties(dev, &rows, &columns);
	if (err)
		return err;
	if (rows != columns) {
		dev_err(dev, "rows and columns must be equal!\n");
		return -EINVAL;
	}

	kscandat->matrix_sz = rows;
	kscandat->row_shift = get_count_order(columns);

	of_property_read_u32(np, "nxp,debounce-delay-ms", &kscandat->deb_clks);
	of_property_read_u32(np, "nxp,scan-delay-ms", &kscandat->scan_delay);
	if (!kscandat->deb_clks || !kscandat->scan_delay) {
		dev_err(dev, "debounce or scan delay not specified\n");
		return -EINVAL;
	}

	return 0;
}