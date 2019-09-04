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
struct cyapa {int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_smbus_read_i2c_block_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 

ssize_t cyapa_i2c_reg_read_block(struct cyapa *cyapa, u8 reg, size_t len,
					u8 *values)
{
	return i2c_smbus_read_i2c_block_data(cyapa->client, reg, len, values);
}