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
 int /*<<< orphan*/  OV2680_REG_GAIN_PK ; 
 int ov2680_read_reg16 (struct ov2680_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ov2680_gain_get(struct ov2680_dev *sensor)
{
	u32 gain;
	int ret;

	ret = ov2680_read_reg16(sensor, OV2680_REG_GAIN_PK, &gain);
	if (ret)
		return ret;

	return gain;
}