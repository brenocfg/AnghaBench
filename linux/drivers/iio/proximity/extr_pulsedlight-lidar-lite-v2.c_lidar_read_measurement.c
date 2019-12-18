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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct lidar_data {int (* xfer ) (struct lidar_data*,int,int /*<<< orphan*/ *,int) ;scalar_t__ i2c_enabled; } ;

/* Variables and functions */
 int LIDAR_REG_DATA_HBYTE ; 
 int LIDAR_REG_DATA_WORD_READ ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int stub1 (struct lidar_data*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int lidar_read_measurement(struct lidar_data *data, u16 *reg)
{
	int ret = data->xfer(data, LIDAR_REG_DATA_HBYTE |
			(data->i2c_enabled ? LIDAR_REG_DATA_WORD_READ : 0),
			(u8 *) reg, 2);

	if (!ret)
		*reg = be16_to_cpu(*reg);

	return ret;
}