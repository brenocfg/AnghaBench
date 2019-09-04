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
struct ov2680_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  OV2680_REG_FORMAT2 ; 
 int ov2680_bayer_order (struct ov2680_dev*) ; 
 int ov2680_mod_reg (struct ov2680_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov2680_hflip_disable(struct ov2680_dev *sensor)
{
	int ret;

	ret = ov2680_mod_reg(sensor, OV2680_REG_FORMAT2, BIT(2), BIT(0));
	if (ret < 0)
		return ret;

	return ov2680_bayer_order(sensor);
}