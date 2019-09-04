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
struct gp2a_data {int /*<<< orphan*/  i2c_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  GP2A_ADDR_OPMOD ; 
 int /*<<< orphan*/  GP2A_CTRL_SSD ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gp2a_enable(struct gp2a_data *dt)
{
	return i2c_smbus_write_byte_data(dt->i2c_client, GP2A_ADDR_OPMOD,
					 GP2A_CTRL_SSD);
}