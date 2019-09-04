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
struct ov2680_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV2680_REG_EXPOSURE_PK_HIGH ; 
 int ov2680_read_reg24 (struct ov2680_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ov2680_exposure_get(struct ov2680_dev *sensor)
{
	int ret;
	u32 exp;

	ret = ov2680_read_reg24(sensor, OV2680_REG_EXPOSURE_PK_HIGH, &exp);
	if (ret)
		return ret;

	return exp >> 4;
}