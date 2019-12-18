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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int i2c_smbus_read_byte_data (struct i2c_client*,scalar_t__) ; 

__attribute__((used)) static inline u16 f75375_read16(struct i2c_client *client, u8 reg)
{
	return (i2c_smbus_read_byte_data(client, reg) << 8)
		| i2c_smbus_read_byte_data(client, reg + 1);
}