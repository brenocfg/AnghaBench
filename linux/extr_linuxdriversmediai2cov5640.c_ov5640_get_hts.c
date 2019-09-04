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
typedef  int u16 ;
struct ov5640_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV5640_REG_TIMING_HTS ; 
 int ov5640_read_reg16 (struct ov5640_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ov5640_get_hts(struct ov5640_dev *sensor)
{
	/* read HTS from register settings */
	u16 hts;
	int ret;

	ret = ov5640_read_reg16(sensor, OV5640_REG_TIMING_HTS, &hts);
	if (ret)
		return ret;
	return hts;
}