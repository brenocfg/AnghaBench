#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  code; } ;
struct ov2680_dev {TYPE_1__ fmt; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  OV2680_REG_FORMAT1 ; 
 int /*<<< orphan*/  OV2680_REG_FORMAT2 ; 
 int /*<<< orphan*/ * ov2680_hv_flip_bayer_order ; 
 int ov2680_read_reg (struct ov2680_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ov2680_bayer_order(struct ov2680_dev *sensor)
{
	u32 format1;
	u32 format2;
	u32 hv_flip;
	int ret;

	ret = ov2680_read_reg(sensor, OV2680_REG_FORMAT1, &format1);
	if (ret < 0)
		return ret;

	ret = ov2680_read_reg(sensor, OV2680_REG_FORMAT2, &format2);
	if (ret < 0)
		return ret;

	hv_flip = (format2 & BIT(2)  << 1) | (format1 & BIT(2));

	sensor->fmt.code = ov2680_hv_flip_bayer_order[hv_flip];

	return 0;
}