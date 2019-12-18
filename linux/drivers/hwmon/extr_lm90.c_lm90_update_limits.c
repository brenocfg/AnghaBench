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
struct lm90_data {int* temp8; int temp_hyst; int* temp11; int flags; scalar_t__ kind; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int LM90_HAVE_EMERGENCY ; 
 int LM90_HAVE_OFFSET ; 
 int LM90_HAVE_REM_LIMIT_EXT ; 
 int /*<<< orphan*/  LM90_REG_R_LOCAL_CRIT ; 
 int /*<<< orphan*/  LM90_REG_R_REMOTE_CRIT ; 
 int /*<<< orphan*/  LM90_REG_R_REMOTE_HIGHH ; 
 int /*<<< orphan*/  LM90_REG_R_REMOTE_HIGHL ; 
 int /*<<< orphan*/  LM90_REG_R_REMOTE_LOWH ; 
 int /*<<< orphan*/  LM90_REG_R_REMOTE_LOWL ; 
 int /*<<< orphan*/  LM90_REG_R_REMOTE_OFFSH ; 
 int /*<<< orphan*/  LM90_REG_R_REMOTE_OFFSL ; 
 int /*<<< orphan*/  LM90_REG_R_TCRIT_HYST ; 
 size_t LOCAL_CRIT ; 
 size_t LOCAL_EMERG ; 
 int /*<<< orphan*/  MAX6659_REG_R_LOCAL_EMERG ; 
 int /*<<< orphan*/  MAX6659_REG_R_REMOTE_EMERG ; 
 size_t REMOTE2_CRIT ; 
 size_t REMOTE2_EMERG ; 
 size_t REMOTE2_HIGH ; 
 size_t REMOTE2_LOW ; 
 size_t REMOTE_CRIT ; 
 size_t REMOTE_EMERG ; 
 size_t REMOTE_HIGH ; 
 size_t REMOTE_LOW ; 
 size_t REMOTE_OFFSET ; 
 struct lm90_data* dev_get_drvdata (struct device*) ; 
 int lm90_read16 (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lm90_read_reg (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int lm90_select_remote_channel (struct lm90_data*,int) ; 
 scalar_t__ max6696 ; 

__attribute__((used)) static int lm90_update_limits(struct device *dev)
{
	struct lm90_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int val;

	val = lm90_read_reg(client, LM90_REG_R_LOCAL_CRIT);
	if (val < 0)
		return val;
	data->temp8[LOCAL_CRIT] = val;

	val = lm90_read_reg(client, LM90_REG_R_REMOTE_CRIT);
	if (val < 0)
		return val;
	data->temp8[REMOTE_CRIT] = val;

	val = lm90_read_reg(client, LM90_REG_R_TCRIT_HYST);
	if (val < 0)
		return val;
	data->temp_hyst = val;

	val = lm90_read_reg(client, LM90_REG_R_REMOTE_LOWH);
	if (val < 0)
		return val;
	data->temp11[REMOTE_LOW] = val << 8;

	if (data->flags & LM90_HAVE_REM_LIMIT_EXT) {
		val = lm90_read_reg(client, LM90_REG_R_REMOTE_LOWL);
		if (val < 0)
			return val;
		data->temp11[REMOTE_LOW] |= val;
	}

	val = lm90_read_reg(client, LM90_REG_R_REMOTE_HIGHH);
	if (val < 0)
		return val;
	data->temp11[REMOTE_HIGH] = val << 8;

	if (data->flags & LM90_HAVE_REM_LIMIT_EXT) {
		val = lm90_read_reg(client, LM90_REG_R_REMOTE_HIGHL);
		if (val < 0)
			return val;
		data->temp11[REMOTE_HIGH] |= val;
	}

	if (data->flags & LM90_HAVE_OFFSET) {
		val = lm90_read16(client, LM90_REG_R_REMOTE_OFFSH,
				  LM90_REG_R_REMOTE_OFFSL);
		if (val < 0)
			return val;
		data->temp11[REMOTE_OFFSET] = val;
	}

	if (data->flags & LM90_HAVE_EMERGENCY) {
		val = lm90_read_reg(client, MAX6659_REG_R_LOCAL_EMERG);
		if (val < 0)
			return val;
		data->temp8[LOCAL_EMERG] = val;

		val = lm90_read_reg(client, MAX6659_REG_R_REMOTE_EMERG);
		if (val < 0)
			return val;
		data->temp8[REMOTE_EMERG] = val;
	}

	if (data->kind == max6696) {
		val = lm90_select_remote_channel(data, 1);
		if (val < 0)
			return val;

		val = lm90_read_reg(client, LM90_REG_R_REMOTE_CRIT);
		if (val < 0)
			return val;
		data->temp8[REMOTE2_CRIT] = val;

		val = lm90_read_reg(client, MAX6659_REG_R_REMOTE_EMERG);
		if (val < 0)
			return val;
		data->temp8[REMOTE2_EMERG] = val;

		val = lm90_read_reg(client, LM90_REG_R_REMOTE_LOWH);
		if (val < 0)
			return val;
		data->temp11[REMOTE2_LOW] = val << 8;

		val = lm90_read_reg(client, LM90_REG_R_REMOTE_HIGHH);
		if (val < 0)
			return val;
		data->temp11[REMOTE2_HIGH] = val << 8;

		lm90_select_remote_channel(data, 0);
	}

	return 0;
}