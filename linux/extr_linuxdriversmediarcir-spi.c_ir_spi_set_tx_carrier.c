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
struct rc_dev {struct ir_spi_data* priv; } ;
struct ir_spi_data {scalar_t__ freq; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int ir_spi_set_tx_carrier(struct rc_dev *dev, u32 carrier)
{
	struct ir_spi_data *idata = dev->priv;

	if (!carrier)
		return -EINVAL;

	idata->freq = carrier;

	return 0;
}