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
struct sd {int dummy; } ;

/* Variables and functions */
 int I2C_BUSY ; 
 int /*<<< orphan*/  M5602_XB_I2C_STATUS ; 
 int m5602_read_bridge (struct sd*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int m5602_wait_for_i2c(struct sd *sd)
{
	int err;
	u8 data;

	do {
		err = m5602_read_bridge(sd, M5602_XB_I2C_STATUS, &data);
	} while ((data & I2C_BUSY) && !err);
	return err;
}