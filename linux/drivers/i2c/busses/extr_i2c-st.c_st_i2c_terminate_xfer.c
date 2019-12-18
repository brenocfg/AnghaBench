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
struct st_i2c_client {scalar_t__ stop; } ;
struct st_i2c_dev {scalar_t__ base; struct st_i2c_client client; } ;

/* Variables and functions */
 scalar_t__ SSC_I2C ; 
 int /*<<< orphan*/  SSC_I2C_REPSTRTG ; 
 int /*<<< orphan*/  SSC_I2C_STOPG ; 
 int /*<<< orphan*/  SSC_I2C_STRTG ; 
 scalar_t__ SSC_IEN ; 
 int /*<<< orphan*/  SSC_IEN_REPSTRTEN ; 
 int /*<<< orphan*/  SSC_IEN_STOPEN ; 
 int /*<<< orphan*/  SSC_IEN_TEEN ; 
 int /*<<< orphan*/  st_i2c_clr_bits (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_i2c_set_bits (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void st_i2c_terminate_xfer(struct st_i2c_dev *i2c_dev)
{
	struct st_i2c_client *c = &i2c_dev->client;

	st_i2c_clr_bits(i2c_dev->base + SSC_IEN, SSC_IEN_TEEN);
	st_i2c_clr_bits(i2c_dev->base + SSC_I2C, SSC_I2C_STRTG);

	if (c->stop) {
		st_i2c_set_bits(i2c_dev->base + SSC_IEN, SSC_IEN_STOPEN);
		st_i2c_set_bits(i2c_dev->base + SSC_I2C, SSC_I2C_STOPG);
	} else {
		st_i2c_set_bits(i2c_dev->base + SSC_IEN, SSC_IEN_REPSTRTEN);
		st_i2c_set_bits(i2c_dev->base + SSC_I2C, SSC_I2C_REPSTRTG);
	}
}