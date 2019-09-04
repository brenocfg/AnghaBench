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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHB_MSB_ADDR_PTR ; 
 int /*<<< orphan*/  GEN_REG_OFFSH ; 
 int /*<<< orphan*/  HOST_SWIF_OFFSH ; 
 int /*<<< orphan*/  REG_CMDRD_ADDRH ; 
 int /*<<< orphan*/  REG_CMDWR_ADDRH ; 
 int s5k6aa_i2c_write (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5k6aa_set_ahb_address(struct i2c_client *client)
{
	int ret = s5k6aa_i2c_write(client, AHB_MSB_ADDR_PTR, GEN_REG_OFFSH);
	if (ret)
		return ret;
	ret = s5k6aa_i2c_write(client, REG_CMDRD_ADDRH, HOST_SWIF_OFFSH);
	if (ret)
		return ret;
	return s5k6aa_i2c_write(client, REG_CMDWR_ADDRH, HOST_SWIF_OFFSH);
}