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
struct si1133_data {unsigned int rsp_seq; int /*<<< orphan*/  regmap; TYPE_1__* client; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ENXIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SI1133_CMD_MINSLEEP_US_HIGH ; 
 int /*<<< orphan*/  SI1133_CMD_MINSLEEP_US_LOW ; 
 int /*<<< orphan*/  SI1133_CMD_RESET_SW ; 
 int /*<<< orphan*/  SI1133_CMD_TIMEOUT_MS ; 
 unsigned int SI1133_MAX_CMD_CTR ; 
 int /*<<< orphan*/  SI1133_REG_COMMAND ; 
 int /*<<< orphan*/  SI1133_REG_RESPONSE0 ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,unsigned int) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si1133_cmd_reset_sw(struct si1133_data *data)
{
	struct device *dev = &data->client->dev;
	unsigned int resp;
	unsigned long timeout;
	int err;

	err = regmap_write(data->regmap, SI1133_REG_COMMAND,
			   SI1133_CMD_RESET_SW);
	if (err)
		return err;

	timeout = jiffies + msecs_to_jiffies(SI1133_CMD_TIMEOUT_MS);
	while (true) {
		err = regmap_read(data->regmap, SI1133_REG_RESPONSE0, &resp);
		if (err == -ENXIO) {
			usleep_range(SI1133_CMD_MINSLEEP_US_LOW,
				     SI1133_CMD_MINSLEEP_US_HIGH);
			continue;
		}

		if ((resp & SI1133_MAX_CMD_CTR) == SI1133_MAX_CMD_CTR)
			break;

		if (time_after(jiffies, timeout)) {
			dev_warn(dev, "Timeout on reset ctr resp: %d\n", resp);
			return -ETIMEDOUT;
		}
	}

	if (!err)
		data->rsp_seq = SI1133_MAX_CMD_CTR;

	return err;
}