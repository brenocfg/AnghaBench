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
struct lidar_data {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIDAR_REG_CONTROL ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int lidar_write_control(struct lidar_data *data, int val)
{
	return i2c_smbus_write_byte_data(data->client, LIDAR_REG_CONTROL, val);
}