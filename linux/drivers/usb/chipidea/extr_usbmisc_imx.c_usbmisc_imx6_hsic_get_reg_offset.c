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
struct imx_usbmisc_data {int index; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int usbmisc_imx6_hsic_get_reg_offset(struct imx_usbmisc_data *data)
{
	int offset, ret = 0;

	if (data->index == 2 || data->index == 3) {
		offset = (data->index - 2) * 4;
	} else if (data->index == 0) {
		/*
		 * For SoCs like i.MX7D and later, each USB controller has
		 * its own non-core register region. For SoCs before i.MX7D,
		 * the first two USB controllers are non-HSIC controllers.
		 */
		offset = 0;
	} else {
		dev_err(data->dev, "index is error for usbmisc\n");
		ret = -EINVAL;
	}

	return ret ? ret : offset;
}