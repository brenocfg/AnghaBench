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
typedef  int u8 ;
struct lidar_data {int (* xfer ) (struct lidar_data*,int,int*,int) ;} ;

/* Variables and functions */
 int stub1 (struct lidar_data*,int,int*,int) ; 

__attribute__((used)) static int lidar_read_byte(struct lidar_data *data, u8 reg)
{
	int ret;
	u8 val;

	ret = data->xfer(data, reg, &val, 1);
	if (ret < 0)
		return ret;

	return val;
}