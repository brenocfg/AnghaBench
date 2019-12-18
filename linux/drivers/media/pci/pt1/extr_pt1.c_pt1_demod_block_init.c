#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct pt1 {TYPE_1__** adaps; } ;
struct i2c_client {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {struct i2c_client* demod_i2c_client; } ;

/* Variables and functions */
 int PT1_NR_ADAPS ; 
 int /*<<< orphan*/  TC90522_I2C_DEV_SAT ; 
 int /*<<< orphan*/  TC90522_I2C_DEV_TER ; 
 int i2c_master_send (struct i2c_client*,int*,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int pt1_demod_block_init(struct pt1 *pt1)
{
	struct i2c_client *cl;
	u8 buf[2] = {0x01, 0x80};
	int ret;
	int i;

	/* reset all terr. & sat. pairs first */
	for (i = 0; i < PT1_NR_ADAPS; i++) {
		cl = pt1->adaps[i]->demod_i2c_client;
		if (strncmp(cl->name, TC90522_I2C_DEV_TER,
			    strlen(TC90522_I2C_DEV_TER)))
			continue;

		ret = i2c_master_send(cl, buf, 2);
		if (ret < 0)
			return ret;
		usleep_range(30000, 50000);
	}

	for (i = 0; i < PT1_NR_ADAPS; i++) {
		cl = pt1->adaps[i]->demod_i2c_client;
		if (strncmp(cl->name, TC90522_I2C_DEV_SAT,
			    strlen(TC90522_I2C_DEV_SAT)))
			continue;

		ret = i2c_master_send(cl, buf, 2);
		if (ret < 0)
			return ret;
		usleep_range(30000, 50000);
	}
	return 0;
}