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
typedef  int uint8_t ;
struct da9034_touch {int last_x; int last_y; int /*<<< orphan*/  da9034_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9034_TSI_XY_LSB ; 
 int /*<<< orphan*/  DA9034_TSI_X_MSB ; 
 int /*<<< orphan*/  DA9034_TSI_Y_MSB ; 
 int da903x_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int read_tsi(struct da9034_touch *touch)
{
	uint8_t _x, _y, _v;
	int ret;

	ret = da903x_read(touch->da9034_dev, DA9034_TSI_X_MSB, &_x);
	if (ret)
		return ret;

	ret = da903x_read(touch->da9034_dev, DA9034_TSI_Y_MSB, &_y);
	if (ret)
		return ret;

	ret = da903x_read(touch->da9034_dev, DA9034_TSI_XY_LSB, &_v);
	if (ret)
		return ret;

	touch->last_x = ((_x << 2) & 0x3fc) | (_v & 0x3);
	touch->last_y = ((_y << 2) & 0x3fc) | ((_v & 0xc) >> 2);

	return 0;
}