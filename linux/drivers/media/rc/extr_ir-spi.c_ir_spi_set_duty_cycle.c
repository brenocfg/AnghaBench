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
typedef  int u32 ;
struct rc_dev {struct ir_spi_data* priv; } ;
struct ir_spi_data {int space; int /*<<< orphan*/  pulse; scalar_t__ negated; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENMASK (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ir_spi_set_duty_cycle(struct rc_dev *dev, u32 duty_cycle)
{
	struct ir_spi_data *idata = dev->priv;
	int bits = (duty_cycle * 15) / 100;

	idata->pulse = GENMASK(bits, 0);

	if (idata->negated) {
		idata->pulse = ~idata->pulse;
		idata->space = 0xffff;
	} else {
		idata->space = 0;
	}

	return 0;
}