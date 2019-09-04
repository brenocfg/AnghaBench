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
struct temperature {int degrees; int fraction; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ read_u8_from_i2c (struct i2c_client*,int,int*) ; 

__attribute__((used)) static void read_temp_from_i2c(struct i2c_client *client, u8 i2c_reg,
			       struct temperature *temp)
{
	u8 degrees, fractional;

	if (read_u8_from_i2c(client, i2c_reg, &degrees) < 0)
		return;

	if (read_u8_from_i2c(client, i2c_reg + 1, &fractional) < 0)
		return;

	temp->degrees = degrees;
	temp->fraction = (fractional & 0xe0) >> 5;
}